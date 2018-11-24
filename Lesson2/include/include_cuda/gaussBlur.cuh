#ifndef GAUSSBLUR_CUH
#define GAUSSBLUR_CUH

#include "image_io.h"
#include <opencv2/opencv.hpp>
//#include <cuda.h>
//#include <cuda_runtime.h>

cv::Mat gauss_blur(cv::Mat inputImage,cv::Mat inputTMP,const float *h_filter, int filterWidth);

#endif
