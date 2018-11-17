//
// Created by anshuai on 18-11-17.
//

#include "image_io.h"

IMAGEIO_NAMESPACE_BEGIN


  void Imageio::imageRead()
  {
    this->image_BGR = cv::imread(this->input_path.c_str(),CV_LOAD_IMAGE_COLOR);
    checkImageioerror(!this->image_BGR.empty());
    checkImageioerror(this->image_BGR.isContinuous());
    return;
  }

  void Imageio::preprocess()
  {
    cv::cvtColor(this->image_BGR,this->image_RGBA,CV_BGR2RGBA);
    checkImageioerror(this->image_RGBA.isContinuous());
    return;
  }

  void Imageio::createGrayimage()
  {
    this->image_GRAY_in.create(this->image_RGBA.rows,this->image_RGBA.cols,CV_8UC1);
    return;
  }

  int Imageio::postprocess(string filename)
  {
    string output_file = this->output_path + "/"+ filename;
    cv::imwrite(output_file,this->image_GRAY_out);
    return 0;
  }
void Imageio::imageShow(cv::Mat image)
{
  cv::imshow("RGBA Image",image);
  cv::waitKey(2000);
}

  void Imageio::pathRead(string path)
  {
    this->input_path = path;
  }

  void Imageio::pathWrite(string path)
  {
    this->output_path=path;
  }


IMAGEIO_NAMESPACE_END
