//
// Created by anshuai on 18-11-17.
//

#ifndef GRAY_IMAGE_IO_H
#define GRAY_IMAGE_IO_H
#include <opencv2/opencv.hpp>
#include "define.h"
#include <iostream>

using namespace std;
IMAGEIO_NAMESPACE_BEGIN

#define checkImageioerror(val) checkimage((val),#val,__FILE__,__LINE__);

template <typename T>
void checkimage(T val,char const* const funcname,char const * const filename,int const linenum);


class Imageio
{

 public:
  cv::Mat image_BGR;
  cv::Mat image_RGBA;
  cv::Mat image_GRAY_in;
  cv::Mat image_GRAY_out;

 private:
  string input_path;
  string output_path;


 public:
  void imageRead();

  void preprocess();

  void createGrayimage();

  int postprocess(string filename);

  void imageShow(cv::Mat);

  void pathWrite(string path);

  void pathRead(string path);
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
#endif //GRAY_IMAGE_IO_H

