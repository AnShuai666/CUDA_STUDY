/*
 * 日期: 2018-12-7
 * 时间: 15:06
 * 姓名: 杨丰拓
 * 对输入图片进行高斯滤波操作
*/

#ifndef GAUSSBLUR_CUH
#define GAUSSBLUR_CUH

#include "image_io.h"
#include <opencv2/opencv.hpp>

/*
 *  @func   高斯模糊输入图片
 *  @param_in   inputImage   输入图片
 *  @param_in   inputTMP     与输入图片大小相等的空白图片
 *  @param_in   *h_filter    高斯滤波核
 *  @param_in   filterWidth  高斯滤波核的边长
 *  @return     output       高斯滤波后的图片
*/
cv::Mat gauss_blur(cv::Mat inputImage,cv::Mat inputTMP,const float *h_filter, int filterWidth);

#endif
