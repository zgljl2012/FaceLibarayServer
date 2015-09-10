
#include "Util.h"
#include "highgui.h"
void _1() {

	IplImage* img = cvLoadImage("person1/p4.jpg");
	Util util;
	// IplImage转化为Mat
	Mat mat = util.iplImageToMat(img);

	// 再将Mat转化为IplImage
	IplImage img2 = util.matToIplImage(&mat);

	char* w1 = "原IplImage";
	char* w2 = "转化而来的Mat";
	char* w3 = "再转化而来的IplImage";
	// 显示IplImage
	cvNamedWindow(w1);
	cvShowImage(w1, img);

	// 显示Mat
	namedWindow(w2);
	imshow(w2, mat);

	// 显示再转化来的IplImage
	cvNamedWindow(w3);
	cvShowImage(w3, &img2);

	cvWaitKey();
	cvDestroyWindow(w1);
	destroyWindow(w2);
	cvDestroyWindow(w3);
}


