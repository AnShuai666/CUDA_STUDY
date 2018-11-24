#include "image_io.h"
#include "gaussBlur.cuh"

int main()
{
	
	imageio::Imageio src_Image;
	src_Image.Readpath("/home/anshuai/yft/November/cuda_gaussBlur/res/2.jpg");
	src_Image.Outputpath("/home/anshuai/yft/November/cuda_gaussBlur/output");
	src_Image.imageRead();
	src_Image.imageShow(src_Image.image_BGR);
	src_Image.preprocess();
    src_Image.imageCreate();
    src_Image.image_tmpout = gauss_blur(src_Image.image_RGBA,src_Image.image_tmpin,src_Image.filter,src_Image.filterWidth);
    src_Image.postprocess("4.jpg");
    src_Image.imageShow(src_Image.image_Blur);
	return 0;
}
