#include <opencv2/opencv.hpp>
#include <cuda_runtime.h>
#include <cuda.h>
#include <device_launch_parameters.h>
#include "rgb2gray.cuh"
using namespace std;
using namespace cv;

__global__ void gray(uchar4* d_in,uchar * d_out,int rows, int cols)
{
	int blockId = gridDim.x*blockIdx.y+blockIdx.x;
	int threadId = blockId*blockDim.x*blockDim.y+blockDim.x*threadIdx.y+threadIdx.x;

	if(threadId<rows*cols)
	{
		uchar4 rgba = d_in[threadId];
		d_out[threadId]=0.299f*rgba.x+0.587f*rgba.y+0.114f*rgba.z;

	}
}

//extern "C"
cv::Mat cudafunc(cv::Mat RGBAImage, cv::Mat GRAYImage)
{

	const int rows=RGBAImage.rows;
	const int cols=RGBAImage.cols;
	int num_pixels=rows*cols;
	uchar4 *h_in;
	uchar *h_out;
	uchar4 *d_in;
	uchar *d_out;

	h_in = (uchar4*)RGBAImage.ptr<unsigned char>(0);
    h_out = (uchar*)GRAYImage.ptr<unsigned char>(0);

	cudaMalloc((void**)&d_in, sizeof(uchar4)*num_pixels);
	cudaMalloc((void**)&d_out,sizeof(uchar)*num_pixels);
	
	cudaMemcpy(d_in,h_in, sizeof(uchar4)*num_pixels,cudaMemcpyHostToDevice);
	const dim3 blocksize(32,32,1);
	//const dim3 gridsize((cols-1+blockDim.x)/blockDim.x,((rows-1+blockDim.y)/blockDim.y),1);
    const dim3 gridsize((cols-1+32)/32,((rows-1+32)/32),1);

	gray <<<gridsize,blocksize>>>(d_in,d_out,rows, cols);
	cudaMemcpy(h_out,d_out,sizeof(uchar)*num_pixels,cudaMemcpyDeviceToHost);

    Mat output(rows,cols,CV_8UC1,h_out);
    cudaFree(d_in);
    cudaFree(d_out);
    return output;

}
 
