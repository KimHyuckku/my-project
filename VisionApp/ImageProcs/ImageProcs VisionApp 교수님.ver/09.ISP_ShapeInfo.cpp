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

	int threshold_min = 60;//0~255
	int threshold_max = 200;//0~255
	//¿Ã¡¯»≠, Binary
	for (size_t i = 0; i < width * height; i++)
	{
		int value = pData[i];

		//if (value > threshold_max)
		//{
		//	pDataBin[i] = 0;
		//}
		//else
		//	pDataBin[i] = 255;
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

	

	return 1;
}
