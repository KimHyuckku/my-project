#pragma once
#include "Common.h"

int main()
{

	//std::string fileName = "../KCCImageNet/stinkbug.png";
	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);

	uchar* pData = src.data;//color pointer
	int length = src.total();//data length
	int channels = src.channels();

	cv::Mat src_Y = cv::Mat(src.rows, src.cols, CV_8UC1);
	cv::Mat src_Cb = cv::Mat(src.rows, src.cols, CV_8UC1);
	cv::Mat src_Cr = cv::Mat(src.rows, src.cols, CV_8UC1);

	cv::Mat src_New = cv::Mat(src.rows, src.cols, CV_8UC3);
	cv::Mat src_Diff = cv::Mat(src.rows, src.cols, CV_8UC3);
	//
	for (size_t row = 0; row < src.rows; row++)
	{
		for (size_t col = 0; col < src.cols; col++)
		{
			//mono
			int index = (row)*src.cols + (col);

			//color	
			if (channels == 3)
			{
				int index_B = index * channels + 0;
				int index_G = index * channels + 1;
				int index_R = index * channels + 2;

				int val_B = pData[index_B];
				int val_G = pData[index_G];
				int val_R = pData[index_R];

				int val_Y = 0.299 * val_R + 0.587 * val_G + 0.114 * val_B;
				int val_Cb = -0.169 * val_R -0.331 * val_G + 0.500 * val_B;
				int val_Cr = 0.500 * val_R -0.419 * val_G -0.0813 * val_B;

				src_Y .data[index] = (uchar)val_Y ;
				src_Cb.data[index] = (uchar)val_Cb;
				src_Cr.data[index] = (uchar)val_Cr;

				val_R = 1.0 * val_Y + 1.402 * val_Cr + 0.000 * val_Cb;
				val_G = 1.0 * val_Y - 0.714 * val_Cr -0.344 * val_Cb;
				val_B = 1.0 * val_Y + 0.000 * val_Cr + 1.772 * val_Cb;

				src_New.data[index_B] = (uchar)val_B;
				src_New.data[index_G] = (uchar)val_G;
				src_New.data[index_R] = (uchar)val_R;
			}
			else//Mono
			{
				src_Y.data[index] = src.data[index];
				src_Cb.data[index] = src.data[index];
				src_Cr.data[index] = src.data[index];
			}
				
		}
	}
	src_Diff = src - src_New;
	return 1;
}
