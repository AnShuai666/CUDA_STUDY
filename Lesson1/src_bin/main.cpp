#include "gray.cuh"
#include "image_io.h"

//extern "C" 
//void func();
int main(int argc,char * argv[])
{
  imageio::Imageio pine;
  pine.pathRead("/home/anshuai/yft/November/error_gray/res/pine.jpg");
  pine.imageRead();
  pine.imageShow(pine.image_BGR);
  pine.preprocess();
  pine.imageShow(pine.image_RGBA);

  pine.createGrayimage();

  pine.image_GRAY_out = cudafunc(pine.image_RGBA,pine.image_GRAY_in);

  pine.pathWrite("/home/anshuai/yft/November/error_gray/output");
  pine.postprocess("graypine.jpg");
  pine.imageShow(pine.image_GRAY_out);
  return 0;
}

