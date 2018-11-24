#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include<opencv2/opencv.hpp>
#include<iostream>
#include "define.h"

using namespace std;
IMAGEIO_NAMESPACE_BEGIN

#define checkImageioerror(val) checkimage((val),#val,__FILE__,__LINE__);
template <typename T>
void checkImage(T val, char const* const funcname ,char const * const filename ,int const linenum);

class Imageio
{
	private :
	string input_path;
	string output_path;
	
	public:
	cv::Mat image_BGR;
	cv::Mat image_RGBA;
	cv::Mat image_tmpin;
    cv::Mat image_tmpout;
	cv::Mat image_Blur;
    float *filter;
    const int filterWidth=9;


	
	void Readpath(string path);	 

	void Outputpath(string path);

	void imageRead();
 
	void preprocess();

	void imageCreate();
	 
	void postprocess(string filename);
	 
	void imageShow(cv::Mat image);
};

template <typename T>
void checkimage(T val,char const* const funcname,char const * const filename,int const linenum)
{
  if(val != 1)
  {
    cerr<<"IMAGE IO ERROR AT: "<<filename<<": "<<linenum<<endl;
    cerr<<"ERROR FUNCNAME IS: "<<funcname<<endl;
    exit(1);
  }
  return;
}
IMAGEIO_NAMESPACE_END


#endif
