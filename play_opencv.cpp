#include <cv.hpp>
#include <math.h>
#include <string.h>
#include <opencv/cv.h>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc,char *argv[])
{
    //cv::Mat img = cv::Mat(240,320,CV_8UC3,cv::Scalar(0,0,255));
    cv::Mat img = imread("201704051756.jpg");

	int width = img.cols;
	int height = img.rows;
    //cv::rectangle(img, cvPoint(250,250), cvPoint(100,100), cvScalar(255,0,0),2);
	//Rect(int a,int b,int c,int d)a,b为矩形的左上角坐标,c,d为矩形的长和宽
    rectangle(img, Rect(100,300,width/2, height/2), cvScalar(98,245,31),2);

	int m = 0;
	for(int i = 310; i < 300+height/2; i+=10)
	{
		int cnt = (300+height/2)/10;
	Point a = Point(100,i);
	Point b = Point(100+width/2, i);
	cv::line(img,a, b, Scalar(0,0,255), 0.1*(m++));

	}
	//设置绘制文本的相关参数
	std::string text = "Hello World!";
	int font_face = cv::FONT_HERSHEY_COMPLEX; 
	double font_scale = 2;
	int thickness = 2;
	int baseline;
	//获取文本框的长宽
	cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
							 
	//将文本框居中绘制
	cv::Point origin; 
	origin.x = img.cols / 2 - text_size.width / 2;
    origin.y = img.rows / 2 + text_size.height / 2;
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
    cv::circle(img,cvPoint(100,100),50,cvScalar(0,255,0),2);
 
	Rect select;//声明矩形
	select.x = origin.x;//左上角坐标
	select.y = origin.y - text_size.height;
	select.width = text_size.width;
	select.height = text_size.height;
	 
	rectangle(img,select,Scalar(0,0,255),3,8,0);//用矩形画矩形窗
    
	cv::namedWindow("test");
    cv::imshow("test",img);
    cv::waitKey(0);
    return 0;
}

