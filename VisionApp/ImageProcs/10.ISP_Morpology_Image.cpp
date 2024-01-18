#pragma once
#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/images/circle_plate.png";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	cv::Mat src_bin;
	cv::threshold(src_gray, src_bin, 150, 255, ThresholdTypes::THRESH_BINARY);

	uchar* pData = src_bin.data;
	size_t width = src_gray.cols;
	size_t height = src_gray.rows;

	Mat src_erosion = Mat::zeros(height, width, CV_8UC1);
	Mat src_dilation = Mat::zeros(height, width, CV_8UC1);

	//침식(erosion)
	//const int SE_sz = 3; int SE_half_sz = SE_sz / 2;
	//int SE_Cross[SE_sz * SE_sz] = {
	//	000,255,000,
	//	255,255,255,
	//	000,255,000 };
	//int SE_Rect[SE_sz * SE_sz] = {
	//	255,255,255,
	//	255,255,255,
	//	255,255,255 };
	const int SE_sz = 5; int SE_half_sz = SE_sz / 2;
	int SE_Cross[SE_sz * SE_sz] = {
		000,000,255,000,000,
		000,000,255,000,000,
		255,255,255,255,255,
		000,000,255,000,000,
		000,000,255,000,000 };
	int SE_Rect[SE_sz * SE_sz] = {
		255,255,255,255,255,
		255,255,255,255,255,
		255,255,255,255,255,
		255,255,255,255,255,
		255,255,255,255,255 };
	// erosion
	uchar* pDst = src_erosion.data;
	for (size_t row = SE_half_sz; row < height - SE_half_sz; row++) {
		for (size_t col = SE_half_sz; col < width - SE_half_sz; col++) {
			//struct element
			bool allone = true;
			for (int h = -SE_half_sz; h <= SE_half_sz; h++) {
				for (int w = -SE_half_sz; w <= SE_half_sz; w++) {
					int index = (row + h) * width + (col + w);
					int index_SE = (h + SE_half_sz) * SE_sz + (w + SE_half_sz);
					uchar input = pData[index];
					//input == 0 : background
					bool condition = (input == 0 && SE_Cross[index_SE] == 255);
					if (condition == true)
					{
						allone = false;
						break;
					}
				}
				if (!allone) break;
			}
			if (allone)
				pDst[row * width + col] = 255;
			else
				pDst[row * width + col] = 0;
		}
	}

	// dilation
	uchar* pErosion = pDst;
	uchar* pDilation = src_dilation.data;
	for (size_t row = SE_half_sz; row < height - SE_half_sz; row++) {
		for (size_t col = SE_half_sz; col < width - SE_half_sz; col++) {

			bool condition = false;
			for (int h = -SE_half_sz; h <= SE_half_sz; h++) {
				for (int w = -SE_half_sz; w <= SE_half_sz; w++) {
					int index = (row + h) * width + (col + w);
					int index_SE = (h + SE_half_sz) * SE_sz + (w + SE_half_sz);
					uchar input = pErosion[index];
					//input == 0 : background
					condition = (input == 255 && SE_Cross[index_SE] == 255);
					if (condition == true) break;
				}
				if (condition == true) break;
			}

			if (condition == true)
			{
				for (int h = -SE_half_sz; h <= SE_half_sz; h++) {
					for (int w = -SE_half_sz; w <= SE_half_sz; w++) {
						int index = (row + h) * width + (col + w);
						int index_SE = (h + SE_half_sz) * SE_sz + (w + SE_half_sz);
						if (SE_Cross[index_SE] == 255)
							pDilation[index] = 255;
					}
				}
			}
		}
	}

	// OpenCV
	{
		/*const int SE_sz = 3; int SE_half_sz = SE_sz / 2;
		int SE_Cross[SE_sz * SE_sz] = {
			000,255,000,
			255,255,255,
			000,255,000 };
		int SE_Rect[SE_sz * SE_sz] = {
			255,255,255,
			255,255,255,
			255,255,255 };*/

		int kernerSz = 10;
		int shape = MorphShapes::MORPH_RECT;
		cv::Size sz = Size(2 * kernerSz + 1, 2 * kernerSz + 1);
		Mat SE = cv::getStructuringElement(shape, sz);

		// 침식 erode
		// src :: src_bin
		Mat src_erode;
		cv::erode(src_bin, src_erode, SE);
		Mat diff_erode = src_bin - src_erode;

		Mat src_dilate;
		cv::dilate(src_bin, src_dilate, SE);
		Mat diff_dilate = src_dilate - src_bin;
		
		// opening
		Mat src_open, src_closing;;
		int type = MorphTypes::MORPH_OPEN;
		cv::morphologyEx(src_bin, src_open, type, SE);
		Mat diff_open = src_bin - src_open;

		type = MorphTypes::MORPH_CLOSE;
		cv::morphologyEx(src_bin, src_closing, type, SE);
		Mat diff_close = src_bin - src_closing;

		int a = 0;
	}
	return 1;
}