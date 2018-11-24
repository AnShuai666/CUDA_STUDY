#include "image_io.h"
#include <opencv2/opencv.hpp>
using namespace cv;
IMAGEIO_NAMESPACE_BEGIN


	void Imageio::Readpath(string path)
	{

		this->input_path=path;
	}

	void Imageio::Outputpath(string path)
	{
		this->output_path=path;
	}

	void Imageio::imageRead()//读取图片到image_BGR;
	{
		this->image_BGR=cv::imread(this->input_path.c_str());
		checkImageioerror(!this->image_BGR.empty());
		checkImageioerror(this->image_BGR.isContinuous());
		return ;
		
	}

	void Imageio::preprocess()//将图片转化为RGBA格式,并存放到image_RGBA中去;
	{
        cv::cvtColor(this->image_BGR,this->image_RGBA,CV_BGR2RGBA);

		return;
	}

	void Imageio::imageCreate()
	{
		this->image_tmpin.create(this->image_BGR.rows,this->image_BGR.cols,CV_8UC4);

        const int blurKernelSigma = 2;

        //归一化处理
        filter = new float[filterWidth * filterWidth];

        float filterSum = 0.f;

        for (int r = -filterWidth / 2; r <= filterWidth / 2; ++r)
        {
          for (int c = -filterWidth / 2; c <= filterWidth / 2; ++c)
          {
            float filterValue = expf(-(float)(c*c + r * r) / (2.f*blurKernelSigma*blurKernelSigma));
            (filter)[(r + filterWidth / 2)*filterWidth + c + filterWidth / 2] = filterValue;
            filterSum += filterValue;
          }
        }//高斯函数

        float normalizationFactor = 1.f / filterSum;

        for (int r = -filterWidth/ 2; r <= filterWidth / 2; ++r)
        {
          for (int c = -filterWidth / 2; c <= filterWidth / 2; ++c)
          {
          (filter)[(r + filterWidth / 2)*filterWidth + c + filterWidth / 2] *= normalizationFactor;
          }
        }

        return;
	}

	void Imageio::postprocess(string filename)//将处理后的图片转换为BGR格式存放到image_Blur中并写入到给定的输出路径;
	{
        cv::cvtColor(this->image_tmpout,this->image_Blur, CV_RGBA2BGR);
		string output_file=this->output_path+"/"+filename;
		cv::imwrite(output_file,this->image_Blur);
	}

	void Imageio::imageShow(cv::Mat image)
	{
		  cv::imshow("RGBA Image",image);
		  cv::waitKey(2000);
	}

IMAGEIO_NAMESPACE_END
