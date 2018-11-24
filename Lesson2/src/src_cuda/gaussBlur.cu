#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "gaussBlur.cuh"
using  namespace std;
using namespace cv;


__global__  void  separate_channels(const uchar4* const d_inputImageRGBA,unsigned char* const d_red,
                                                                        unsigned char* const d_green,
                                    					                unsigned char* const d_blue,
                                    					                int rows,int cols)
{
    const int r=blockIdx.y*blockDim.y+threadIdx.y;
    const int c=blockIdx.x*blockDim.x+threadIdx.x;
    int idx=r*cols+c;

    if(r>=rows||c>=cols)
    {
        return;
    }

    d_red[idx]=d_inputImageRGBA[idx].x;
    d_green[idx]=d_inputImageRGBA[idx].y;
    d_blue[idx]=d_inputImageRGBA[idx].z;

}

__global__ void gaussblur(const unsigned char* const d_red, unsigned char* const d_redBlurred ,
                           float* d_filter,int rows,int cols,const int filterWidth)
{
    const int r=blockIdx.y*blockDim.y+threadIdx.y;
    const int c=blockIdx.x*blockDim.x+threadIdx.x;
    const int idx=r*cols+c;

    if(r>=rows||c>=cols)
    {
            return;
    }

	float color = 0.0f;
	for (int filter_y = 0; filter_y < filterWidth; filter_y++) {
		for (int filter_x = 0; filter_x < filterWidth; filter_x++) {
			int image_x = c + filter_x - filterWidth / 2;
			int image_y = r + filter_y - filterWidth / 2;
			image_x  = min(max(image_x , 0), cols - 1);
			image_y  = min(max(image_y , 0), rows - 1);

			float filter_value = d_filter[filter_y*filterWidth + filter_x];
			color += filter_value * static_cast<float>(d_red[image_y *cols + image_x]);
		}
	}
	d_redBlurred[idx] = color;

}

__global__ void recombineChannels(const unsigned char* const d_redBlurred,const unsigned char* const d_greenBlurred,
                                  const unsigned char* const d_blueBlurred, uchar4* const d_outputImageRGBA,
                                  int rows,int cols)
{
     const int r=blockIdx.y*blockDim.y+threadIdx.y;
     const int c=blockIdx.x*blockDim.x+threadIdx.x;
     const int idx=r*cols+c;

     if(r>=rows||c>=cols)
     {
           return;
     }

    unsigned char red = d_redBlurred[idx];
	unsigned char green = d_greenBlurred[idx];
	unsigned char blue = d_blueBlurred[idx];

	uchar4 outputPixel = make_uchar4(red, green, blue, 255);

	d_outputImageRGBA[idx] = outputPixel;
}


cv::Mat gauss_blur(cv::Mat inputImage,cv::Mat inputTMP,const float *h_filter, int filterWidth)
{
    uchar4 *h_inputImageRGBA,*h_outputImage;
    uchar4 *d_inputImageRGBA,*d_outputImageRGBA;
    unsigned char  *d_red,*d_green,*d_blue,*d_redBlurred,*d_greenBlurred,*d_blueBlurred;

    float *d_filter;

    h_inputImageRGBA=(uchar4 *)inputImage.ptr<unsigned char>(0);
    h_outputImage=(uchar4 *)inputTMP.ptr<unsigned char>(0);


    const int rows=inputImage.rows;
    const int cols=inputImage.cols;
    const size_t numPixels=rows*cols;

    //分配显存
    cudaMalloc((void **)&d_inputImageRGBA,sizeof(uchar4)*numPixels);
    cudaMalloc((void **)&d_outputImageRGBA,sizeof(uchar4)*numPixels);
    cudaMalloc((void **)&d_red,sizeof(unsigned char)*numPixels);
    cudaMalloc((void **)&d_green,sizeof(unsigned char)*numPixels);
    cudaMalloc((void **)&d_blue,sizeof(unsigned char)*numPixels);
    cudaMalloc((void **)&d_redBlurred,sizeof(unsigned char)*numPixels);
    cudaMalloc((void **)&d_greenBlurred,sizeof(unsigned char)*numPixels);
    cudaMalloc((void **)&d_blueBlurred,sizeof(unsigned char)*numPixels);
    cudaMalloc((void **)&d_filter,sizeof(float)*filterWidth*filterWidth);

    //将CPU中h_inputImageRGBA的数据复制到GPU中d_inputImageRGBA
    cudaMemcpy(d_inputImageRGBA,h_inputImageRGBA,sizeof(uchar4)*numPixels,cudaMemcpyHostToDevice);
    //将CPU中h_filter的数据复制到GPU中d_filter
    cudaMemcpy(d_filter,h_filter,sizeof(float)*filterWidth*filterWidth,cudaMemcpyHostToDevice);

    const dim3 blockSize(32,32,1);
    const dim3 gridSize((cols-1+32)/32,(rows-1+32)/32,1);

    //将输入图片分离为三个颜色通道
    separate_channels<<<gridSize,blockSize>>>(d_inputImageRGBA,d_red,d_green,d_blue,rows,cols);
    cudaDeviceSynchronize();

    //对单颜色通道进行高斯模糊
    gaussblur<<<gridSize,blockSize>>>(d_red,d_redBlurred,d_filter,rows,cols,filterWidth);
    cudaDeviceSynchronize();
    gaussblur<<<gridSize,blockSize>>>(d_green,d_greenBlurred,d_filter,rows,cols,filterWidth);
    cudaDeviceSynchronize();
    gaussblur<<<gridSize,blockSize>>>(d_blue,d_blueBlurred,d_filter,rows,cols,filterWidth);
    cudaDeviceSynchronize();

    //合并高斯模糊后的三条颜色通道
    recombineChannels<<<gridSize,blockSize>>>(d_redBlurred,d_greenBlurred,d_blueBlurred,d_outputImageRGBA,rows,cols);
    cudaDeviceSynchronize();

    //将GPU中d_outputImageRGBA的数据复制到CPU中h_outputImage
    cudaMemcpy(h_outputImage,d_outputImageRGBA,sizeof(uchar4)*numPixels,cudaMemcpyDeviceToHost);
    Mat output(rows,cols,CV_8UC4,h_outputImage);

    cudaFree(d_red);
    cudaFree(d_green);
    cudaFree(d_blue);
    cudaFree(d_redBlurred);
    cudaFree(d_greenBlurred);
    cudaFree(d_blueBlurred);
    cudaFree(d_filter);
    cudaFree(d_inputImageRGBA);
    cudaFree(d_outputImageRGBA);


    return output;
}

