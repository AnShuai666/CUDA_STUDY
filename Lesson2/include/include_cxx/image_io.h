/*
 * 日期: 2018-12-7
 * 时间: 13:49
 * 姓名: 杨丰拓
 * 图像的输入处理与输出处理
*/


#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include<opencv2/opencv.hpp>
#include<iostream>
#include "define.h"

using namespace std;
IMAGEIO_NAMESPACE_BEGIN

#define checkImageioerror(val) checkimage((val),#val,__FILE__,__LINE__);

/***************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~模板函数的声明~~~~~~~~~~~~~~~~~~~~~~~*
 ***************************************************************/
template <typename T>
void checkImage(T val, char const* const funcname ,char const * const filename ,int const linenum);


/***************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~Imageio类的声明~~~~~~~~~~~~~~~~~~~~~~~*
 ***************************************************************/
class Imageio
{
	private :
	string input_path;
	string output_path;
	
	public:
/***************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~数据成员的声明~~~~~~~~~~~~~~~~~~~~~~~~~*
 ***************************************************************/
	cv::Mat image_BGR;
	cv::Mat image_RGBA;
	cv::Mat image_in;
    cv::Mat image_out;
	cv::Mat image_Blur;
    float filter[81];
    int filterWidth=9;


/***************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~成员函数的声明~~~~~~~~~~~~~~~~~~~~~~~~~*
 ***************************************************************/

  /*
   *  @property  成员函数
   *  @func      写入输入文件路径
   *  @param_in  path   文件输入路径
  */
   void Readpath(string path);

  /*
   *  @property  成员函数
   *  @func      写入输出文件路径
   *  @param_in  path   文件输出路径
  */
   void Outputpath(string path);

  /*
   *  @property  成员函数
   *  @func      读取图片到image_BGR
  */
   void imageRead();

  /*
   *  @property  成员函数
   *  @func      将image_BGR转化为RGBA格式存放到image_RGBA中去,创建9*9的高斯卷积核
  */
   void preprocess();

  /*
   *  @property  成员函数
   *  @func      创建与image_BGR同样大小的空白图片image_in
  */
   void imageCreate();

  /*
   *  @property  成员函数
   *  @func      将image_out转化为BGR格式存放到image_Blur中去,将image_Blur写入到指定输出路径
   *  @param_in  filename   输出图片的文件名
  */
   void postprocess(string filename);

  /*
   *  @property  成员函数
   *  @func      在窗口显示图片,持续2s
   *  @param_in  image    在窗口显示的图片
  */
   void imageShow(cv::Mat image);
};

/*
 *  @property  模板函数
 *  @func      判断语句是否正常执行
 *  @param_in  val        被测语句的布尔值
 *  @param_in  funcname   被测语句的字符串表示
 *  @param_in  filename   被测语句所在文件
 *  @param_in  linenum    被测语句所在行数
 */
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
