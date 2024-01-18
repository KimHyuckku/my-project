#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/shapes.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	uchar* pData = src_gray.data;
	size_t width = src_gray.cols;
	size_t height = src_gray.rows;

	cv::Mat src_bin = Mat::zeros(cv::Size(width, height), CV_8UC1);
	cv::Mat src_obj = Mat::zeros(cv::Size(width, height), CV_8UC1);
	uchar* pDataBin = src_bin.data;

	int threshold_min = 60;
	int threshold_max = 200;

	for (size_t i = 0; i < height * width; i++)
	{
		int value = pData[i];
		(value > threshold_max) ? pDataBin[i] = 0 : pDataBin[i] = 255;
	}
	src_obj = src_bin & src_gray;

	RNG rng(12345);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(src_bin.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
	}

	//countours... vector[i]...  ..n-th 개수를 출력해보세요.
	//5개니까 
	Mat src_color;
	cv::cvtColor(src_gray, src_color, ColorConversionCodes::COLOR_GRAY2BGR);

	for (size_t i = 0; i < 5; i++)
	{
		double area = contourArea(contours[i]);
		RotatedRect rrt = minAreaRect(contours[i]);
		
		double arcLen = arcLength(contours[i], true);

		Point ptTxt = Point(rrt.boundingRect().x, rrt.boundingRect().y);
		string msg;
		msg = std::format("area = {:.1f}", area);
		putText(src_color, msg, Point(ptTxt.x, ptTxt.y + 30 * 0), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("x,y = {:.1f}, {:.1f}", rrt.center.x, rrt.center.y);
		putText(src_color, msg, Point(ptTxt.x, ptTxt.y + 30 * 1), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("length = {:.1f}", arcLen);
		putText(src_color, msg, Point(ptTxt.x, ptTxt.y + 30 * 2), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		cv::rectangle(src_color, rrt.boundingRect2f().tl(), rrt.boundingRect2f().br(), CV_RGB(0, 0, 255));
		cv::drawMarker(src_color, rrt.center, CV_RGB(255, 0, 0));

		const int ptSz = 4;
		Point2f pt[ptSz];
		rrt.points(pt);

		for (size_t i = 0; i < ptSz; i++)
		{
			cv::line(src_color, pt[i % ptSz], pt[(i + 1) % ptSz], CV_RGB(255, 0, 255), 1);
		}

	}
	return 1;
}
#if 0
#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/stop_img.png"; // stop_img.png // shapes.jpg
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);
	cv::Mat src_da = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);
	Mat src_bin;
	cv::cvtColor(src_da, src_bin, ColorConversionCodes::COLOR_BGR2GRAY);
	Mat src_HSV;
	cv::cvtColor(src, src_HSV, ColorConversionCodes::COLOR_BGR2HSV);

	uchar* pData = src_da.data;
	size_t width = src_da.cols;
	size_t height = src_da.rows;

	uchar* HSV_pData = src_HSV.data;

	int threshold_r = 200;
	int threshold_g = 100;
	int threshold_b = 100;
	int sum_brightness = 0;

	uchar blu, grn, red;

	for (size_t row = 0; row < src_da.rows; row++)
	{
		for (size_t col = 0; col < src_da.cols; col++)
		{
			blu = pData[row * src_da.cols * 3 + col * 3];
			grn = pData[row * src_da.cols * 3 + col * 3 + 1];
			red = pData[row * src_da.cols * 3 + col * 3 + 2];

			sum_brightness = HSV_pData[row * src_HSV.cols * 3 + col * 3];

			if (blu < threshold_b && grn < threshold_g && red > threshold_r)
			{
				pData[row * src_da.cols * 3 + col * 3] = 255;
				pData[row * src_da.cols * 3 + col * 3 + 1] = 255;
				pData[row * src_da.cols * 3 + col * 3 + 2] = 255;
			}
			else
			{
				pData[row * src_da.cols * 3 + col * 3] = 0;
				pData[row * src_da.cols * 3 + col * 3 + 1] = 0;
				pData[row * src_da.cols * 3 + col * 3 + 2] = 0;
			}
		}
	}


	RNG rng(12345);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	int CoGx, CoGy, x_length, y_length;
	int x_max = 0, x_min = width, y_max = 0, y_min = height;

	for (size_t n = 0; n < contours[0].size(); n++)
	{
		if (contours[0].at(n).x > x_max) x_max = contours[0].at(n).x;
		if (contours[0].at(n).x < x_min) x_min = contours[0].at(n).x;
		if (contours[0].at(n).y > y_max) y_max = contours[0].at(n).y;
		if (contours[0].at(n).y < y_min) y_min = contours[0].at(n).y;
	}
	x_length = x_max - x_min;
	y_length = y_max - y_min;
	int radius = (y_max - y_min) / 2;

	CoGx = (x_max + x_min) / 2;
	CoGy = (y_max + y_min) / 2;

	cv::line(src_da, Point(CoGx - 10, CoGy - 10), Point(CoGx + 10, CoGy - 10), CV_RGB(255, 0, 255));
	cv::line(src_da, Point(CoGx - 10, CoGy + 10), Point(CoGx + 10, CoGy + 10), CV_RGB(200, 0, 255));

	cv::circle(src_HSV, Point(CoGx, CoGy), (y_max - y_min) / 2, CV_RGB(128, 0, 200), 2);

	double area = contourArea(contours[0]);
	double arcLen = arcLength(contours[0], true);


	string msg;
	msg = std::format("Area = {:.1f}", area);
	putText(src_HSV, msg, Point(CoGx + radius, CoGy + 30 * 0), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
	msg = std::format("X,Y = {:d}, {:d}", CoGx, CoGy);
	putText(src_HSV, msg, Point(CoGx + radius, CoGy + 30 * 1), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
	msg = std::format("Length = {:.1f}", arcLen);
	putText(src_HSV, msg, Point(CoGx + radius, CoGy + 30 * 2), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
	msg = std::format("Radius = {:d}", radius);
	putText(src_HSV, msg, Point(CoGx + radius, CoGy + 30 * 3), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
	msg = std::format("AvgBrigntness = {:d}", sum_brightness / (src_HSV.cols * src_HSV.rows));
	putText(src_HSV, msg, Point(CoGx + radius, CoGy + 30 * 4), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
	return 1;
#endif