/*
 * 日期: 2018-12-7
 * 时间: 15:00
 * 姓名: 杨丰拓
*/

#include "image_io.h"
#include "gaussBlur.cuh"
#include <chrono>

using namespace cv;
int main()
{
  imageio::Imageio image1;
  image1.Readpath("/home/anshuai/yft/November/cuda_gaussBlur/res/pine.jpg");
  image1.Outputpath("/home/anshuai/yft/November/cuda_gaussBlur/output");

  image1.imageRead();
  image1.preprocess();
  image1.imageCreate();
  image1.image_out = gauss_blur(image1.image_RGBA,image1.image_in,image1.filter,image1.filterWidth);
  image1.postprocess("4.jpg");
  image1.imageShow(image1.image_BGR);

  image1.imageShow(image1.image_Blur);

  return 0;
}

/*




 */