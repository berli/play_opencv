/*************************************************************************
    > File Name: lsd_lines.cpp
    > Author: berli
    > Mail: berli@tencent.com 
    > Created Time: Fri Jun  7 18:58:21 2019
 ************************************************************************/

//#include <opencv2/ximgproc.hpp> //wd 20190508
//#include <opencv2/line_descriptor/descriptor.hpp> //wd 20190508
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() 
{
	VideoCapture cap("rtsp://admin:hk654123@192.168.2.211:554/h264/ch1/main/av_stream");
	while(true)
	{
		Mat frame;
		cap>>frame;
		imshow("hai kang", frame);
		waitKey(10);

	}

	return 0;
#if 0
   //string path = "line.jpg";
   string path = "../line.png";
   Mat image = imread(path, IMREAD_GRAYSCALE);
   blur(image, image, Size(3,3)); // 使用3x3内核来降噪
   Canny(image, image, 50, 200, 3); // Apply canny edge

   // Create and LSD detector with standard
   /*
     LSD_REFINE_NONE，没有改良的方式；
     LSD_REFINE_STD，标准改良方式，将带弧度的线（拱线）拆成多个可以逼近原线段的直线度；
     LSD_REFINE_ADV，进一步改良方式，计算出错误警告数量，通过增加精度，减少尺寸进一步精确直线。
   */
   //Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
   Ptr<cv::ximgproc::FastLineDetector> detector = ximgproc::createFastLineDetector();
   double start = double(getTickCount());
   vector<Vec4f> lines_std;

   // Detect the lines
   detector->detect(image, lines_std);

   // Show found lines
   Mat drawnLines(image);
   detector->drawSegments(drawnLines, lines_std);

   Mat only_lines(image.size(), image.type());
   detector->drawSegments(only_lines, lines_std);

   imshow("【lsd直线检测】", drawnLines);
   imshow("【仅仅是直线】", only_lines);

   waitKey(0);
#endif
   return 0;
}

