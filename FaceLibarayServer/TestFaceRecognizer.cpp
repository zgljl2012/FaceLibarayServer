#include "highGUI.h"
#include "cv.h"
#include <opencv2/opencv.hpp>  
#include <iostream>
#include <vector>
#include <cctype>
#include <iostream>
#include <string>
#include <iterator>
using namespace std;
using namespace cv;

#include "MyFaceRecognizer.h"

MyFaceRecognizer rec;
string file = "FaceLibrary.xml";


// ¥Ê¥¢“ª–©»À¡≥ø‚
void save(){
	vector<Mat> images;
	vector<int> labels;
	char* person1_str[] = {
		"person1/p4.jpg",
		"person1/p4_1.jpg",
		"person1/p4_4.jpg"
	};
	for (int i = 0; i < 3; i++) {
		images.push_back(imread(person1_str[i], CV_LOAD_IMAGE_GRAYSCALE));
		labels.push_back(1);
	}
	images.push_back(imread("person2/p2.jpg", CV_LOAD_IMAGE_GRAYSCALE));
	labels.push_back(2);
	rec.train(images, labels);
	rec.save(file.c_str());
}

void _testFaceRecognizer(int argc, char** argv){
	if (argc < 2){
		argv[1] = "person1/p4.jpg";
		save();
		return;
	}
	rec.load(file.c_str());
	if (argc == 3 && strcmp(argv[1], "add")==0) {
		vector<Mat> images;
		vector<int> labels;
		images.push_back(imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE));
		labels.push_back(1);
		rec.add(images, labels);
		return;
	}
	
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	int predicted = rec.predict(img);
	cout << predicted << endl;
	return;
}










