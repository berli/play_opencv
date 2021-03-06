#include "cvUtil.h"

using namespace std;


int main(int argc,char *argv[])
{
    //cv::Mat img = cv::Mat(240,320,CV_8UC3,cv::Scalar(0,0,255));
	string file ;
	if( argc == 2 )
		file = argv[1];
	else
		file = "201704051756.jpg";
    cv::Mat img = imread(file);

	//hough line
	cvUtil util;
	vector<Point>vecLines;
	util.detectLines(img, vecLines);
	cv::namedWindow("test");
    cv::imshow("test",img);
    cv::waitKey(0);
	//end hough line

	return 0;

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
	
	string text = "你好Hello World";
	vector<string>vecText;
	vecText.push_back(text);

	text = "Hello World 123 ";
	vecText.push_back(text);
	//frameText(img, vecText);

	text = "中文字体显示 ";
	vecText.push_back(text);
	
	text = "adb体显示 ";
	vecText.push_back(text);

	text = "123 adb显示 ";
	vecText.push_back(text);

	text = "中文字示 ";
	vecText.push_back(text);
	vecText.push_back(text);
	vecText.push_back(text);
	vecText.push_back(text);
	vecText.push_back(text);
	vecText.push_back(text);

	util.frameTextCh(img, vecText);
    
	for(int i = 200; i < 500; )
	{
    //在原图画一条直线
	cv::Point start = cv::Point(i, 300); //直线起点
	cv::Point end = cv::Point(300,400);   //直线终点
	cv::line(img, start, end, cv::Scalar(0, 0, 255));
	cout<<"x:"<<i<<" angle:"<<util.singleLineAngle(start, end)<<endl;

	i+= 10;
	}
	Point rhip(333.184845,271.260010);
	//Point rknee(466.571777,308.241119); 
	Point rknee(466.571777,271.260010); 
	cout<<" angle:"<<util.singleLineAngle(rhip, rknee)<<endl;

	util.putCircle(img, Point(350,350), 10);

	cv::Scalar color(0,0,255);
	util.drawArrow(img, rhip, rknee,color);

	Point p1(100, 100);
	Point p2(400, 500);
	Point c(200, 300);
	util.drawArrow(img, c,p1,color);
	util.drawArrow(img, c,p2,color);
	cout<<"two line angle:"<<util.getAngelOfTwoVector(p1, p2, c)<<endl;

	cv::namedWindow("test");
    cv::imshow("test",img);
    cv::waitKey(0);

	////////////////////////////
	cv::Mat src(768, 1024,CV_8UC3);
	src.setTo(0);

	std::vector<cv::Point > contour;
	contour.push_back(cv::Point(0, 0));
	contour.push_back(cv::Point(100,0));
	contour.push_back(cv::Point(20, 200));
	contour.push_back(cv::Point(200, 200));
	contour.push_back(cv::Point(671, 263));
	//contour.push_back(cv::Point(1024, 643));


	std::vector<std::vector<cv::Point >> contours;
	contours.push_back(contour);

	//填充区域之前，首先采用polylines()函数，可以使填充的区域边缘更光滑
	//cv::polylines(src, contours, true, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);//第2个参数可以采用contour或者contours，均可
	//cv::fillPoly(src, contours, cv::Scalar(255, 255, 255));//fillPoly函数的第二个参数是二维数组！！

	//cv::imshow("原图", src);
	//cv::waitKey(0);

	return 0;
}

