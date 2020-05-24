/*
 * 日期: 2018-12-7
 * 时间: 14:30
 * 姓名: 杨丰拓
*/

#include "image_io.h"
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
      //归一化处理
      const int blurKernelSigma = 2;
      float filterSum = 0.f;

      for (int r = -filterWidth / 2; r <= filterWidth / 2; ++r)
      {
        for (int c = -filterWidth / 2; c <= filterWidth / 2; ++c)
        {
          float filterValue = expf(-(float)(c*c + r * r) / (2.f*blurKernelSigma*blurKernelSigma));
          filter[(r + filterWidth / 2)*filterWidth + c + filterWidth / 2] = filterValue;
          filterSum += filterValue;
        }
      }//高斯函数

      float normalizationFactor = 1.f / filterSum;

      for (int r = -filterWidth/ 2; r <= filterWidth / 2; ++r)
      {
        for (int c = -filterWidth / 2; c <= filterWidth / 2; ++c)
        {
          filter[(r + filterWidth / 2)*filterWidth + c + filterWidth / 2] *= normalizationFactor;
        }
      }

		return;
	}

	void Imageio::imageCreate()
	{
		this->image_in.create(this->image_BGR.rows,this->image_BGR.cols,CV_8UC4);
        return;
	}

	void Imageio::postprocess(string filename)//将处理后的图片转换为BGR格式存放到image_Blur中并写入到给定的输出路径;
	{
        cv::cvtColor(this->image_out,this->image_Blur, CV_RGBA2BGR);
		string output_file=this->output_path+"/"+filename;
		cv::imwrite(output_file,this->image_Blur);

	}

	void Imageio::imageShow(cv::Mat image)
	{
		  cv::imshow("RGBA Image",image);
		  cv::waitKey(2000);
	}

IMAGEIO_NAMESPACE_END
