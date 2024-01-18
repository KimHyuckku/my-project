#include "Common.h"

void main()
{
	Mat gray = Mat::zeros(Size(300, 100), CV_32FC1);

	cv::line(gray, Point(10, 20), Point(50, 20), 255, 2);
	cv::line(gray, Point(50, 50), Point(50, 20), 255, 2);

	cv::line(gray, Point(60, 10), Point(60, 50), 255, 2);

	cv::line(gray, Point(20, 60), Point(60, 60), 255, 2);
	cv::line(gray, Point(60, 60), Point(60, 90), 255, 2);
	cv::line(gray, Point(60, 90), Point(20, 90), 255, 2);
	cv::line(gray, Point(20, 90), Point(20, 60), 255, 2);

	cv::line(gray, Point(100, 20), Point(150, 20), 255, 2);
	cv::line(gray, Point(125, 20), Point(125, 10), 255, 2);
	cv::circle(gray, Point(125, 40), 15, 255, 2);

	cv::line(gray, Point(160, 10), Point(160, 70), 255, 2);
	cv::line(gray, Point(160, 30), Point(150, 30), 255, 2);
	cv::line(gray, Point(160, 50), Point(150, 50), 255, 2);

	cv::line(gray, Point(110, 70), Point(150, 70), 255, 2);
	cv::line(gray, Point(150, 70), Point(150, 90), 255, 2);

	cv::line(gray, Point(210, 20), Point(250, 20), 255, 2);
	cv::line(gray, Point(250, 20), Point(250, 60), 255, 2);

	cv::line(gray, Point(200, 60), Point(260, 60), 255, 2);
	cv::line(gray, Point(230, 60), Point(230, 90), 255, 2);


	int a = 0;
}