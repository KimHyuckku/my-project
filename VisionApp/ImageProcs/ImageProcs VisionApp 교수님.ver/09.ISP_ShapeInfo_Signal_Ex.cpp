#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/stop_img.png";
	cv::Mat src_color = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);

	Mat src_hsv;
	cvtColor(src_color, src_hsv, COLOR_BGR2HSV);

	Mat src_hsv_bin, src_hsv_bin_Red_1, src_hsv_bin_Red_2;
	inRange(src_hsv, Scalar(160, 180, 0), Scalar(180, 255, 255), src_hsv_bin_Red_1);
	inRange(src_hsv, Scalar(0, 180, 0), Scalar(10, 255, 255), src_hsv_bin_Red_2);
	src_hsv_bin = src_hsv_bin_Red_1 + src_hsv_bin_Red_2;

	RNG rng(12345);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_hsv_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	//morphology remove noise
	//src_hsv_bin

	int kernelSz = 2;
	int shape = MorphShapes::MORPH_CROSS;
	cv::Size sz = Size(2 * kernelSz + 1, kernelSz + 1);
	Mat SE = getStructuringElement(shape, sz);

	Mat src_erode;
	cv::erode(src_hsv_bin, src_erode, SE);
	Mat diff_erode = src_hsv_bin - src_erode;

	Mat src_open, src_closing;
	int type = MorphTypes::MORPH_OPEN;
	morphologyEx(src_hsv_bin, src_open, type, SE);

	type = MorphTypes::MORPH_CLOSE;
	morphologyEx(src_open, src_closing, type, SE);

	Mat drawing = src_color.clone();// Mat::zeros(src_color.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		//drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
		drawContours(drawing, contours, (int)i, color, CV_FILLED);
	}

	//find max area object
	double max_area = 0;
	size_t max_area_index = 0;
	for (size_t i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (max_area < area)
		{
			max_area = area;
			max_area_index = i;
		}
	}
	drawContours(drawing, contours, (int)max_area_index, CV_RGB(255, 0, 0), CV_FILLED);

	const Point* pts = (const cv::Point*)Mat(contours[max_area_index]).data;
	int npts = Mat(contours[max_area_index]).rows;
	cv::polylines(drawing, &pts, &npts, 1, true, Scalar(200, 200, 200));
	cv::fillConvexPoly(drawing, pts, npts, cv::Scalar(0, 255, 200));

	return 1;
}
