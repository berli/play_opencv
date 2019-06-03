/*************************************************************************
    > File Name: cvUtil.h
    > Author: berli
    > Mail: berli@tencent.com 
    > Created Time: 2019年06月03日 星期一 19时05分33秒
 ************************************************************************/
#ifndef CV_UTIL_
#define CV_UTIL_
#include<iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <string.h>
//#include <opencv/cv.h>
#include <stdio.h>
#include <opencv2/freetype.hpp>

using namespace std;
using namespace cv;

#define  PI 3.1415926

class cvUtil
{
public:
	cvUtil()
	{
	}
	
	~cvUtil()
	{
	}
	
	float computeAngle(cv::Point pt0, cv::Point pt1);

	Scalar getFilledColor();

	void frameText(cv::Mat&img, vector<string>&text, const bool&filled = true, const bool&transparent = true, const float&alpha = 0.3);

	void frameTextCh(cv::Mat&img, vector<string>&text, const int&ix=0, const int&iy =0, const bool&filled = true, const bool&transparent = true, const float&alpha = 0.3);


	void frameText(cv::Mat&img,const string&text);

};



#endif

