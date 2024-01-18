#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/stop_img.png"; // stop_img.png // shapes.jpg
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);
	cv::Mat src_da = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);
	Mat src_HSV;
	cv::cvtColor(src, src_HSV, ColorConversionCodes::COLOR_BGR2HSV);

	uchar* pData = src_da.data;
	uchar* HSV_pData = src_HSV.data;
	size_t width = src_da.cols;
	size_t height = src_da.rows;

	int threshold_r = 190;
	int threshold_g = 100;
	int threshold_b = 100;
	int sum_brightness = 0;
	int sum_red = 0;
	int color_area = 0;

	uchar blu, grn, red;

	for (size_t row = 0; row < src_da.rows; row++)
	{
		for (size_t col = 0; col < src_da.cols; col++)
		{
			blu = pData[row * src_da.cols * 3 + col * 3];
			grn = pData[row * src_da.cols * 3 + col * 3 + 1];
			red = pData[row * src_da.cols * 3 + col * 3 + 2];

			if(blu < threshold_b && grn < threshold_g && red > threshold_r)
			{
				sum_red += red;
				sum_brightness += HSV_pData[row * src_da.cols * 3 + col * 3 + 2];
				pData[row * src_da.cols * 3 + col * 3] = 255;
				pData[row * src_da.cols * 3 + col * 3 + 1] = 255;
				pData[row * src_da.cols * 3 + col * 3 + 2] = 255;
				color_area++;
			}
			else
			{
				pData[row * src_da.cols * 3 + col * 3] = 0;
				pData[row * src_da.cols * 3 + col * 3 + 1] = 0;
				pData[row * src_da.cols * 3 + col * 3 + 2] = 0;
			}
		}
	}
	Mat src_bin;
	cv::cvtColor(src_da, src_bin, ColorConversionCodes::COLOR_BGR2GRAY);

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
		CoGx = (x_max + x_min)/2;
		CoGy = (y_max + y_min)/2;
		float rad = (y_max - y_min) / 2;
		
		cv::circle(src_HSV, Point(CoGx, CoGy), rad, CV_RGB(128, 0, 200), 2);
		cv::Point2f point2(CoGx, CoGy);
		minEnclosingCircle(contours[0], point2, rad);

		double area = contourArea(contours[0]);
		double arcLen = arcLength(contours[0], true);

		string msg;
		msg = std::format("Area = {:.1f}", area);
		putText(src_HSV, msg, Point(CoGx + rad, CoGy - 30 * 2), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("X,Y = {:d}, {:d}", CoGx, CoGy);
		putText(src_HSV, msg, Point(CoGx + rad, CoGy - 30 * 1), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("Length = {:.1f}", arcLen);
		putText(src_HSV, msg, Point(CoGx + rad, CoGy + 30 * 0), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("Radius = {:d}", (y_max - y_min) / 2);
		putText(src_HSV, msg, Point(CoGx + rad, CoGy + 30 * 1), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("AvgBrightness");
		putText(src_HSV, msg, Point(CoGx + rad, CoGy + 30 * 2), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("= {:d}, {:d}", sum_brightness / color_area, sum_red / color_area);
		putText(src_HSV, msg, Point(CoGx + rad, CoGy + 30 * 3), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
	
		
	return 1;
}