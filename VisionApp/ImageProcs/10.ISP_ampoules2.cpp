#pragma once
#include "ISP.h"

int main()
{
	int img_counts = 8;
	for (size_t img_index = 1; img_index <= img_counts; img_index++)
	{
		std::string fileName = "../KCCImageNet/images/ampoules/ampoules_" + std::format("{:02d}.png", img_index);

		cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);
		cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
		Mat src_draw, src_gray_Eq;
		cv::cvtColor(src_gray, src_draw, ColorConversionCodes::COLOR_GRAY2BGR);
		cv::equalizeHist(src_gray, src_gray_Eq);

		uchar* pData = src_gray.data;
		size_t width = src_gray.cols;
		size_t height = src_gray.rows;
		uchar* Eq_pData = src_gray_Eq.data;

		cv::Mat src_bin = Mat::zeros(cv::Size(width, height), CV_8UC1);
		uchar* pDataBin = src_bin.data;

		int threshold = 210;
		int white_up = 230, white_down = 300;
		int line_up = 80, line_down = 120;

		for (size_t row = 0; row < height; row++)
		{
			for (size_t col = 0; col < width; col++)
			{
				int index = (row)*width + (col);

				if (row > white_up && row < white_down)
				{
					int value = pData[index];
					if (value >= threshold) pDataBin[index] = 255;
					else pDataBin[index] = 0;
				}
				else
				{
					pDataBin[index] = 0;
				}
			}
		}

		int kernerSz = 3;												// Èò»ö µ¥ÀÌÅÍ Ã£°í ´Ùµë±â
		int shape = MorphShapes::MORPH_ELLIPSE;
		cv::Size sz = Size(2 * kernerSz + 1, 2 * kernerSz + 1);
		Mat SE = cv::getStructuringElement(shape, sz);

		Mat src_bin_open, src_bin_open_close;
		int type = MorphTypes::MORPH_OPEN;
		cv::morphologyEx(src_bin, src_bin_open, type, SE);
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
			drawContours(src_draw, contours, (int)i, CV_RGB(255, 255, 0), CV_FILLED);		//Èò»ö µ¥ÀÌÅÍºÎºÐ ³ë¶õ»öÀ¸·Î Ä¥
		}

		cv::line(src_draw, Point(0, line_up), Point(width, line_up), CV_RGB(255, 0, 0), 1);
		cv::line(src_draw, Point(0, line_down), Point(width, line_down), CV_RGB(255, 0, 0), 1);

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
			int white_min_area = 2800;
			int amp_data1 = 0, amp_data2 = 0, amp_line = 0, div1, div2 = 0;
			int data_left = 60, data_right = 20, data_center = 40;
			int data_top = 65, data_bottom = 200;

			string msg;
			cv::drawMarker(src_draw, Point(CoGx, CoGy), CV_RGB(255, 0, 0), MarkerTypes::MARKER_CROSS);
			msg = std::format("{:d}", i);
			putText(src_draw, msg, Point(CoGx - data_right, CoGy - 15), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 0, 10), 1, 8);
			msg = std::format("{:.1f}", area);
			putText(src_draw, msg, Point(CoGx - data_right, CoGy + 15), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 0, 10), 1, 8);

			if (area > white_min_area && CoGx - data_left >= 0)
			{
				for (size_t row = data_top; row < data_bottom; row++)
				{
					amp_data1 = 0;
					for (size_t col = CoGx - data_left; col < CoGx - data_right; col++)
					{
						int index = (row)*width + (col);
						amp_data1 += Eq_pData[index];
					}
					if (amp_data2 == 0) amp_data2 = amp_data1;

					div1 = abs(amp_data1 - amp_data2);

					if (div1 > div2)
					{
						div2 = div1;
						amp_line = row;
					}
					amp_data2 = amp_data1;

				}
				cv::line(src_draw, Point(CoGx - data_left, amp_line), Point(CoGx - data_right, amp_line), CV_RGB(0, 0, 255), 1);

				if (amp_line <= line_down && amp_line >= line_up)
					cv::circle(src_draw, Point(CoGx - data_center, amp_line), 20, CV_RGB(10, 255, 0), 2);
				else
					cv::drawMarker(src_draw, Point(CoGx - data_center, amp_line), CV_RGB(255, 0, 0), MarkerTypes::MARKER_TILTED_CROSS, 30, 2);
			}
		}

		int a = 0;
	}
	return 1;
}