#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/brake_disk/brake_disk_part_07.png";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
	Mat src_color;
	cv::cvtColor(src_gray, src_color, ColorConversionCodes::COLOR_GRAY2BGR);

	uchar* pData = src_gray.data;
	size_t width = src_gray.cols;
	size_t height = src_gray.rows;

	cv::Mat src_bin = Mat::zeros(cv::Size(width, height), CV_8UC1);
	uchar* pDataBin = src_bin.data;

	int threshold_max = 240;
	for (size_t i = 0; i < height * width; i++)
	{
		int value = pData[i];
		(value > threshold_max) ? pDataBin[i] = 255 : pDataBin[i] = 0;
	}

	int kernerSz = 5;
	int shape = MorphShapes::MORPH_ELLIPSE;
	cv::Size sz = Size(4 * kernerSz + 1, 4 * kernerSz + 1);
	Mat SE = cv::getStructuringElement(shape, sz);

	Mat src_bin_open, src_bin_open_close;
	int type = MorphTypes::MORPH_OPEN;
	cv::morphologyEx(src_bin, src_bin_open, type, SE);
	type = MorphTypes::MORPH_CLOSE;
	cv::morphologyEx(src_bin_open, src_bin_open_close, type, SE);



	RNG rng(12345);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_bin_open_close, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(src_bin_open_close.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, CV_FILLED);
		drawContours(src_color, contours, (int)i, CV_RGB(255, 255, 0), CV_FILLED);
	}

	//countours... vector[i]...  ..n-th 개수를 출력해보세요.
	//5개니까 
	
	for (size_t i = 0; i < contours.size(); i++)
	{
		int CoGx, CoGy;
		int accX = 0, accY = 0;
		int length = contours[i].size();
		int x_max = 0, x_min = width, y_max = 0, y_min = height;

		for (size_t n = 0; n < contours[i].size(); n++)
		{
			accX += contours[i].at(n).x;
			accY += contours[i].at(n).y;
			if (contours[i].at(n).x > x_max) x_max = contours[i].at(n).x;
			if (contours[i].at(n).x < x_min) x_min = contours[i].at(n).x;
			if (contours[i].at(n).y > y_max) y_max = contours[i].at(n).y;
			if (contours[i].at(n).y < y_min) y_min = contours[i].at(n).y;
		}
		/*CoGx = accX / length;
		CoGy = accY / length;*/

		CoGx = (x_max + x_min) / 2;
		CoGy = (y_max + y_min) / 2;

		cv::line(src_color, Point(CoGx - (x_max-x_min)/2, CoGy), Point(CoGx + (x_max - x_min) / 2, CoGy), CV_RGB(255, 0, 255));
		cv::line(src_color, Point(CoGx, CoGy - (y_max - y_min) / 2), Point(CoGx, CoGy + (y_max - y_min) / 2), CV_RGB(200, 0, 255));
		

		double area = contourArea(contours[i]);
		double arcLen = arcLength(contours[i], true);

		string msg;
		msg = std::format("area = {:.1f}", area);
		putText(src_color, msg, Point(CoGx, CoGy - 30 * 1), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 10, 255), 2, 8);
		msg = std::format("ecc = x,y = {:d}, {:d}", CoGx, CoGy);
		putText(src_color, msg, Point(CoGx, CoGy + 30 * 0), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 10, 255), 2, 8);
		msg = std::format("length = {:.1f}", arcLen);
		putText(src_color, msg, Point(CoGx, CoGy + 30 * 1), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 10, 255), 2, 8);
		msg = std::format("radius = {:d}", (x_max - x_min) / 2);
		putText(src_color, msg, Point(CoGx, CoGy + 30 * 2), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 10, 255), 2, 8);	
	}
	return 1;
}