#include <opencv2/opencv.hpp>
#include <math.h>
#include <string.h>
//#include <opencv/cv.h>
#include <stdio.h>
#include <opencv2/freetype.hpp>
#include "cvUtil.h"

using namespace std;
using namespace cv;

cvUtil::cvUtil()
{
	color_index = 0;
    Scalar r,g,b;
    
    r = Scalar(229, 61, 25);//r
    cVecScalar.push_back(r);
    
    r = Scalar(236, 49, 194);//r
    cVecScalar.push_back(r);

    b = Scalar(91, 229, 25);//b
    cVecScalar.push_back(b);

    r = Scalar(49, 129, 236);//r
    cVecScalar.push_back(r);
    
    r = Scalar(163, 25, 229);//r
    cVecScalar.push_back(r);
    
    r = Scalar(130, 191, 255);//seeTaFace color
    cVecScalar.push_back(r);

    r = Scalar(129, 129, 125);//蒙板
    cVecScalar.push_back(r);

    g = Scalar(25, 193, 229);//g
    cVecScalar.push_back(g);
}

cvUtil::~cvUtil()
{
}

float cvUtil::singleLineAngle(cv::Point pt0, cv::Point pt1)
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
	
	//float a =  atanf((float)dy / dx);
	float a =  atan2f((float)dy, dx);
	float angle = a*180/PI ;
	return angle;
}

void cvUtil::InitColor()
{
	color_index =0;
}

Scalar cvUtil::getFilledColor()
{
	color_index %= cVecScalar.size();
	cout<<"cVecScalar.size:"<<cVecScalar.size()<<" color_index:"<<color_index<<endl;
	return cVecScalar[color_index++];
}

void cvUtil::frameText(cv::Mat&img, vector<string>&text, const bool&filled, const bool&transparent, const float&alpha)
{
	//设置绘制文本的相关参数
	//std::string text = "Hello World!";
	int font_face = cv::FONT_HERSHEY_COMPLEX; 
	double font_scale = 1;
	int baseline;
	//获取文本框的长宽
	int y = 0;
	cv::Point origin; 

	Mat dst;
	if(transparent)
	{
		img.copyTo(dst);
	}

	for(auto&e:text)
	{
		int text_thickness =2;
		cv::Size text_size = cv::getTextSize(e, font_face, font_scale, text_thickness, &baseline);
								 
		//将文本框居中绘制
		origin.x = 0;
		if( y == 0)
			origin.y = text_size.height+10;
	    origin.y += y;
		y += origin.y;
		//cout<<"y:"<<y<<endl;
 
		Rect select;//声明矩形
		select.x = origin.x;//左上角坐标
		select.y = origin.y - text_size.height - 5;
		select.width = text_size.width;
		select.height = text_size.height+12;
		
		int thickness = 3;
    	if(filled)
    		thickness = FILLED;
		Scalar s = getFilledColor();
		rectangle(img,select, s,thickness,8,0);//用矩形画矩形窗
		//rectangle(img,select,Scalar(0,0,255),3,8,0);//用矩形画矩形窗
		
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

		cv::putText(img, e, origin, font_face, font_scale, cv::Scalar(0, 0, 255), text_thickness, 8, 0);
	    
	}

	if( transparent)
	{
		float beta = ( 1.0 - alpha );
		cv::addWeighted(dst, alpha, img, beta, 0 ,dst);
		img = dst;
	}
}

void cvUtil::frameTextCh(cv::Mat&img, vector<string>&text, const int&ix, const int&iy, const bool&filled, const bool&transparent, const float&alpha)
{
	//设置绘制文本的相关参数
	//std::string text = "Hello World!";
	int fontHeight = 25;
	int baseline;
	//获取文本框的长宽
	int y = 0;
	cv::Point origin; 
	origin.x = 0;
	origin.y = 0;

	Ptr<freetype::FreeType2> ft2;
	ft2 = freetype::createFreeType2();
	//ft2->loadFontData( "xjlFont.ttf", 0 );
	ft2->loadFontData( "simsun.ttc", 0 );
	
	Mat dst;
	if(transparent)
	{
		img.copyTo(dst);
	}

	int max_width = 0;
	for(auto&e:text)
	{
		int text_thickness =2;
		cv::Size text_size = ft2->getTextSize(e, fontHeight, text_thickness, &baseline);
		if( text_size.width > max_width)
			max_width = text_size.width;
	}

	InitColor();
	for(auto&e:text)
	{
		int text_thickness =2;
		cv::Size text_size = ft2->getTextSize(e, fontHeight, text_thickness, &baseline);
		
		//cout<<"cv::Size height:"<<text_size.height<<endl;
		//cout<<"cv::Size width:"<<text_size.width<<endl;
								 
		//将文本框居中绘制
		if( y == 0)
		{
			origin.y += text_size.height+10;
			y += origin.y;
		}
		else
			origin.y = y;
		y += text_size.height+10;
		//cout<<"y:"<<y<<endl;
 
		Rect select;//声明矩形
		select.x = origin.x;//左上角坐标
		select.y = origin.y - text_size.height - 5;
		//select.width = text_size.width;
		select.width = max_width;
		select.height = text_size.height+12;
		
		int thickness = 3;
    	if(filled)
    		thickness = FILLED;
		Scalar s = getFilledColor();
		rectangle(img,select, s,thickness,8,0);//用矩形画矩形窗
		//rectangle(img,select, s,3,8,0);//用矩形画矩形窗
		
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
		cv::Point textOrigin = origin;
		textOrigin.y = select.y;
		//cout<<"origin.y:"<<origin.y<<endl;
		//cout<<"textOrigin.y:"<<textOrigin.y<<endl<<endl;
		//ft2->putText(img, e, textOrigin, fontHeight, cv::Scalar(0, 0, 255), text_thickness, 8, 0);
		ft2->putText(img, e, textOrigin, fontHeight, cv::Scalar(255, 255, 255), text_thickness, 8, 0);
	}

	if( transparent)
	{
		float beta = ( 1.0 - alpha );
		cv::addWeighted(dst, alpha, img, beta, 0 ,dst);
		img = dst;
	}
}

void cvUtil::frameText(cv::Mat&img,const string&text)
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

void cvUtil::putCircle(cv::Mat&img,const Point&center, const int& radius, const Scalar&color, const int&thickness, const bool&transparent, const float&alpha)
{
    cv::circle(img, center, radius, color, thickness);

	if( transparent)
	{
		Mat dst;
		img.copyTo(dst);
		float beta = ( 1.0 - alpha );
		cv::addWeighted(dst, alpha, img, beta, 0 ,dst);
		img = dst;
	}
}

