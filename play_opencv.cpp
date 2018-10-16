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
    cv::rectangle(img, Rect(100,300,width/2, height/2), cvScalar(98,245,31),2);
	for(int i = 320; i < 300+height/2; i+=20)
	{
	Point a = Point(100,i);
	Point b = Point(100+width/2, i);
	cv::line(img,a, b, Scalar(0,0,255));

	}
    cv::circle(img,cvPoint(100,100),50,cvScalar(0,255,0),2);
 
    cv::namedWindow("test");
    cv::imshow("test",img);
    cv::waitKey(0);
    return 0;
}

