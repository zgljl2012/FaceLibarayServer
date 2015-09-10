
#include "MyFaceRecognizer.h"

// 默认构造函数
MyFaceRecognizer::MyFaceRecognizer() {
	// 创建识别器
	model = createLBPHFaceRecognizer(1, 8, 8, 8, 60);
}

// 存储特征库
void MyFaceRecognizer::save(const char* filename) {
	this->filename = filename;
	model->save(filename);
}

// 装载特征库
void MyFaceRecognizer::load(const char* filename) {
	this->filename = filename;
	model->load(filename);
}

// 添加人脸信息
void MyFaceRecognizer::add(vector<Mat> faces, vector<Labels> labels) {
	model->update(faces, labels);
	model->save(this->filename);
}

// 训练系统
void MyFaceRecognizer::train(vector<Mat> faces, vector<Labels> labels) {
	model->train(faces, labels);
}

// 人脸识别
Labels MyFaceRecognizer::predict(Mat img) {
	return model->predict(img);
}


// 获取此时的特征库路径
string MyFaceRecognizer::getFilePath() {
	return this->filename;
}






