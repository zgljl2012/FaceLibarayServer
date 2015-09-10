/*==========================================================
* 文件名 : Util
* 日期	 : 2015/9/7
* 功能   : 实现一些工具函数，如Mat和IplImage的相互转换等
* ==========================================================*/

#include "cv.h"
using namespace cv;

#ifndef _UTIL_H_
#define _UTIL_H_

class Util {
public:
	// Mat转化为IplImage
	static IplImage matToIplImage(Mat* mat);

	// IplImage转化为Mat
	static Mat iplImageToMat(IplImage* img);

};

IplImage Util::matToIplImage(Mat* mat){
	return IplImage(*mat);
}

Mat Util::iplImageToMat(IplImage* img) {
	return Mat(img, true);
}

#endif
