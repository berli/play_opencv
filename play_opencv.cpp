#include <opencv2/opencv.hpp>
#include <math.h>
#include <string.h>
//#include <opencv/cv.h>
#include <stdio.h>

using namespace std;
using namespace cv;

#define  PI 3.1415926

float computeAngle(cv::Point pt0, cv::Point pt1)
{
	int dx = pt1.x - pt0.x;
	int dy = pt1.y - pt0.y;
	if(dx == 0)
	{
		if(dy < 0)
		{
			return CV_PI / 2.0;
		}
		else if(dy > 0)
		{
			return -CV_PI / 2.0;
		}
		else
		{
			return 0.0;
		}
			
	}
	
	float a =  atanf((float)dy / dx);
	float angle = a*180/PI ;
	return angle;
}

void frameText(cv::Mat&img, vector<string>&text)
{
	//设置绘制文本的相关参数
	//std::string text = "Hello World!";
	int font_face = cv::FONT_HERSHEY_COMPLEX; 
	double font_scale = 1;
	int thickness = 2;
	int baseline;
	//获取文本框的长宽
	int y = 0;
	cv::Point origin; 
	for(auto&e:text)
	{
		cv::Size text_size = cv::getTextSize(e, font_face, font_scale, thickness, &baseline);
								 
		//将文本框居中绘制
		origin.x = 0;
		if( y == 0)
			origin.y = text_size.height+10;
	    origin.y += y;
		y += origin.y;
		cout<<"y:"<<y<<endl;
		/*
    	void cv::putText(  
		 cv::Mat& img, // 待绘制的图像  
		 const string& text, // 待绘制的文字  
		 cv::Point origin, // 文本框的左下角  
		 int fontFace, // 字体 (如cv::FONT_HERSHEY_PLAIN)  
		 double fontScale, // 尺寸因子，值越大文字越大  
		 cv::Scalar color, // 线条的颜色（RGB）  
		 int thickness = 1, // 线条宽度  
		 int lineType = 8, // 线型（4邻域或8邻域，默认8邻域）  
		 bool bottomLeftOrigin = false // true='origin at lower left'  
		 ); 
		*/
		cv::putText(img, e, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
 
		Rect select;//声明矩形
		select.x = origin.x;//左上角坐标
		select.y = origin.y - text_size.height - 5;
		select.width = text_size.width;
		select.height = text_size.height+12;
		 
		rectangle(img,select,Scalar(0,0,255),3,8,0);//用矩形画矩形窗
	}
}

void frameText(cv::Mat&img,const string&text)
{
	//设置绘制文本的相关参数
	//std::string text = "Hello World!";
	int font_face = cv::FONT_HERSHEY_COMPLEX; 
	double font_scale = 1;
	int thickness = 2;
	int baseline;
	//获取文本框的长宽
	cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
							 
	//将文本框居中绘制
	cv::Point origin; 
	origin.x = img.cols / 2 - text_size.width / 2;
    origin.y = img.rows / 2 + text_size.height / 2;
	origin.x = 0;
    origin.y = text_size.height+10;
	/*
    void cv::putText(  
	 cv::Mat& img, // 待绘制的图像  
	 const string& text, // 待绘制的文字  
	 cv::Point origin, // 文本框的左下角  
	 int fontFace, // 字体 (如cv::FONT_HERSHEY_PLAIN)  
	 double fontScale, // 尺寸因子，值越大文字越大  
	 cv::Scalar color, // 线条的颜色（RGB）  
	 int thickness = 1, // 线条宽度  
	 int lineType = 8, // 线型（4邻域或8邻域，默认8邻域）  
	 bool bottomLeftOrigin = false // true='origin at lower left'  
	 ); 
	*/
	cv::putText(img, text, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
 
	Rect select;//声明矩形
	select.x = origin.x;//左上角坐标
	select.y = origin.y - text_size.height - 5;
	select.width = text_size.width;
	select.height = text_size.height+12;
	 
	rectangle(img,select,Scalar(0,0,255),3,8,0);//用矩形画矩形窗
}

int main(int argc,char *argv[])
{
    //cv::Mat img = cv::Mat(240,320,CV_8UC3,cv::Scalar(0,0,255));
    cv::Mat img = imread("201704051756.jpg");

	int width = img.cols;
	int height = img.rows;
    //cv::rectangle(img, cvPoint(250,250), cvPoint(100,100), cv::Scalar(255,0,0),2);
	//Rect(int a,int b,int c,int d)a,b为矩形的左上角坐标,c,d为矩形的长和宽
    rectangle(img, Rect(100,300,width/2, height/2), cv::Scalar(98,245,31),2);

	int m = 0;
	for(int i = 310; i < 300+height/2; i+=10)
	{
		int cnt = (300+height/2)/10;
	    Point a = Point(100,i);
	    Point b = Point(100+width/2, i);
	//    cv::line(img,a, b, Scalar(0,0,255), 0.1*(m++));
	}
    cv::circle(img,cv::Point(100,100),50,cv::Scalar(0,255,0),2);
	
	string text = "Hello World";
	//frameText(img, text);
	vector<string>vecText;
	vecText.push_back(text);
	vecText.push_back(text);
	frameText(img, vecText);
    
	cv::namedWindow("test");
    cv::imshow("test",img);
    cv::waitKey(0);

		cv::Mat src(768, 1024,CV_8UC3);
	src.setTo(0);

	std::vector<cv::Point > contour;
	contour.reserve(6);
	contour.push_back(cv::Point(389,253));
	contour.push_back(cv::Point(0, 529));
	contour.push_back(cv::Point(0, 768));
	contour.push_back(cv::Point(1024, 768));
	contour.push_back(cv::Point(1024, 643));
	contour.push_back(cv::Point(671, 263));

	cout<<computeAngle(cv::Point(100,100), cv::Point(0, 0))<<endl;

	std::vector<std::vector<cv::Point >> contours;
	contours.push_back(contour);

	//填充区域之前，首先采用polylines()函数，可以使填充的区域边缘更光滑
	cv::polylines(src, contours, true, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);//第2个参数可以采用contour或者contours，均可
	cv::fillPoly(src, contours, cv::Scalar(255, 255, 255));//fillPoly函数的第二个参数是二维数组！！

	cv::imshow("原图", src);
	cv::waitKey(0);
    
	return 0;
}

