/*===========================================
* 文件名 : MyFaceRecognizer
* 日期	 : 2015/9/6
* 功能   : 实现人脸识别
* ============================================*/

#ifndef _MYFACERECOGNIZER_H_
#define _MYFACERECOGNIZER_H_
#include <vector>
#include "cv.h"
#include <opencv2/opencv.hpp>  
using std::vector;
using namespace cv;

// 标签类型
typedef int Labels;

class MyFaceRecognizer {

public:
	// 默认构造函数
	MyFaceRecognizer();

public:
	// 存储特征库
	void save(const char* filename);
	// 装载特征库
	void load(const char* filename);
	// 添加人脸信息
	void add(vector<Mat> faces, vector<Labels> labels);
	// 训练系统
	void train(vector<Mat> faces, vector<Labels> labels);
	// 人脸识别
	Labels predict(Mat img);
	// 获取此时的特征库路径
	string getFilePath();

private:
	string filename;				// 特征库路径
	Ptr<FaceRecognizer> model;		// 识别器

};


#endif
