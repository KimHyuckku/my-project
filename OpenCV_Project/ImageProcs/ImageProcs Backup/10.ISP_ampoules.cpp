#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/embossed_09.png";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat draw = src.clone();

	uchar* pData = src_gray.data;
	size_t width = src_gray.cols;
	size_t height = src_gray.rows;

	cv::Mat src_bin = Mat::zeros(cv::Size(width, height), CV_8UC1);
	uchar* pDataBin = src_bin.data;

	float s = 1.f;
	Mat dst = src_gray + (src_gray - 250 ) * s;


	Mat edges, thres;
	adaptiveThreshold(dst, thres, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 3, 5);
	
	// °¡¿ì½Ã¾È ºí·¯ Àû¿ë
	GaussianBlur(dst, dst, Size(5, 5), 0);

	// Canny ¿§Áö °ËÃâ
	
	Canny(dst, edges, 100, 200);

	
	int kernerSz = 3;												// Èò»ö µ¥ÀÌÅÍ Ã£°í ´Ùµë±â
	int shape = MorphShapes::MORPH_RECT;
	cv::Size sz = Size(2 * kernerSz + 1, 2 * kernerSz + 1);
	Mat SE = cv::getStructuringElement(shape, sz);

	Mat edges_make_circle, edges_make_circle_close;
	int type = MorphTypes::MORPH_DILATE;
	cv::morphologyEx(edges, edges_make_circle, type, SE);


	kernerSz = 1;												// Èò»ö µ¥ÀÌÅÍ Ã£°í ´Ùµë±â
	shape = MorphShapes::MORPH_RECT;
	sz = Size(4 * kernerSz + 1, 2 * kernerSz + 1);
	SE = cv::getStructuringElement(shape, sz);
	type = MorphTypes::MORPH_CLOSE;
	cv::morphologyEx(edges_make_circle, edges_make_circle_close, type, SE);

	vector<cv::Vec3f> circles;
	cv::HoughCircles(edges_make_circle_close, circles, cv::HOUGH_GRADIENT, 1, 30, 100, 30, 10, 80);

	for (size_t j = 0; j < circles.size(); ++j)
	{
		cv::Point center(cvRound(circles[j][0]), cvRound(circles[j][1]));
		int radius = cvRound(circles[j][2]);

		cv::circle(draw, center, radius, cv::Scalar(0, 255, 0), 2);
		int a = 0;
	}

	


	int threshold_max = 220;
	int threshold_min = 190;

	for (size_t row = 0; row < height; row++)
	{
		for (size_t col = 0; col < width; col++)
		{
			int index = (row)*width + (col);

			if (row > 230 && row < 300)// && col>100 && col < 570)
			{
				int value = pData[index];
				if (value > threshold_max /* && value < threshold_max*/) pDataBin[index] = 255;
				else pDataBin[index] = 0;
			}
			else
			{
				pDataBin[index] = 0;
			}
		}
	}

	kernerSz = 3;												// Èò»ö µ¥ÀÌÅÍ Ã£°í ´Ùµë±â
	shape = MorphShapes::MORPH_ELLIPSE;
	sz = Size(2 * kernerSz + 1, 2 * kernerSz + 1);
	SE = cv::getStructuringElement(shape, sz);

	Mat src_bin_open, src_bin_open_close;
	type = MorphTypes::MORPH_OPEN;
	cv::morphologyEx(src_bin, src_bin_open, type, SE);

	kernerSz = 5;
	shape = MorphShapes::MORPH_ELLIPSE;
	sz = Size(4 * kernerSz + 1, 4 * kernerSz + 1);
	SE = cv::getStructuringElement(shape, sz);

	type = MorphTypes::MORPH_CLOSE;
	cv::morphologyEx(src_bin_open, src_bin_open_close, type, SE);	// Èò»ö µ¥ÀÌÅÍ Ã£°í ´Ùµë±â end

	RNG rng(12345);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_bin_open_close, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(src_bin_open_close.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, CV_FILLED);
		drawContours(draw, contours, (int)i, CV_RGB(255, 255, 0), CV_FILLED);		//Èò»ö µ¥ÀÌÅÍºÎºÐ ³ë¶õ»öÀ¸·Î Ä¥
	}

	for (size_t i = 0; i < contours.size(); i++)			// Èò»ö µ¥ÀÌÅÍ ºÎºÐ Ã£°í
	{
		int CoGx, CoGy;										// Èò»ö µ¥ÀÌÅÍ Áß¾Ó
		int x_max = 0, x_min = width, y_max = 0, y_min = height;

		for (size_t n = 0; n < contours[i].size(); n++)
		{
			if (contours[i].at(n).x > x_max) x_max = contours[i].at(n).x;
			if (contours[i].at(n).x < x_min) x_min = contours[i].at(n).x;
			if (contours[i].at(n).y > y_max) y_max = contours[i].at(n).y;
			if (contours[i].at(n).y < y_min) y_min = contours[i].at(n).y;
		}
		CoGx = (x_max + x_min) / 2;
		CoGy = (y_max + y_min) / 2;

		double area = contourArea(contours[i]);
		int min_area = 2800;
		int amp_side = 20, amp_middle = 40;
		int amp_compare_error = 8000;
		int amp_data1=0, amp_data2=0;

		string msg;
		cv::drawMarker(draw, Point(CoGx, CoGy), CV_RGB(255, 0, 0), MarkerTypes::MARKER_CROSS);
		msg = std::format("{:d}", i);
		putText(draw, msg, Point(CoGx - 20, CoGy - 15), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("{:.1f}", area);
		putText(draw, msg, Point(CoGx-20, CoGy + 15), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 0, 10), 1, 8);

		if (area > min_area && CoGx-60 >= 0)
		{
			for (size_t row = CoGy - 100; row < CoGy - 60; row++)
			{
				for (size_t col = CoGx - 60; col < CoGx - 20; col++)
				{
					int index = (row)*width + (col);
					amp_data1 += pData[index];
				}
			}
			msg = std::format("{:d}", amp_data1);
			putText(draw, msg, Point(CoGx - 60, CoGy - 60), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 0, 10), 1, 8);
			cv::rectangle(draw, Point(CoGx - 60, CoGy - 100), Point(CoGx - 20, CoGy - 60), CV_RGB(0, 0, 255));
			for (size_t row = CoGy - 140; row < CoGy - 100; row++)
			{
				for (size_t col = CoGx - 60; col < CoGx - 20; col++)
				{
					int index = (row)*width + (col);
					amp_data2 += pData[index];
				}
			}
			msg = std::format("{:d}", amp_data2);
			putText(draw, msg, Point(CoGx - 60, CoGy - 100), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 0, 250), 1, 8);
			cv::rectangle(draw, Point(CoGx - 60, CoGy - 140), Point(CoGx - 20, CoGy - 101), CV_RGB(0, 255, 255));
			
			if (amp_data2 < amp_data1 - amp_compare_error)
			{
				cv::drawMarker(draw, Point(CoGx - 40, CoGy - 140), CV_RGB(255, 0, 0), MarkerTypes::MARKER_TILTED_CROSS, 30, 2);
			}
		}
	}

	return 1;
}