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
		std::cout << "Object[" << i << "] 개수는" << contours[i].size() << "입니다." << std::endl;
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
		const int ptSz = 4;
		Point pt[ptSz];
		pt[0].x = x_min; pt[0].y = y_min;//좌상
		pt[1].x = x_max; pt[1].y = y_min;//우상
		pt[2].x = x_max; pt[2].y = y_max;//우하
		pt[3].x = x_min; pt[3].y = y_max;//좌하

		for (size_t i = 0; i < ptSz; i++)
		{
			cv::line(src_color, pt[i % ptSz], pt[(i + 1) % ptSz], CV_RGB(255, 0, 255));
		}

		CoGx = accX / length;
		CoGy = accY / length;
		std::cout << "Object[" << i + 1 << "] CoG.x = " << CoGx << " CoG.y = " << CoGy << std::endl;

		cv::line(src_color, Point(CoGx - 10, CoGy - 10), Point(CoGx + 10, CoGy - 10), CV_RGB(255, 0, 255));
		cv::line(src_color, Point(CoGx - 10, CoGy + 10), Point(CoGx + 10, CoGy + 10), CV_RGB(200, 0, 255));
	}


	

	return 1;
}