#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena_gray.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	cv::Mat src_gray_blur = src_gray.clone();

	//for (size_t i = 0; i < src_gray_blur.cols * src_gray_blur.rows; i++)
	//{
	//	if (src_gray_blur.data[i] < 5 || src_gray_blur.data[i] >250)
	//	{
	//		src_gray_blur.data[i] =(src_gray_blur.data[i - 1] + 
	//								src_gray_blur.data[i + 1] +
	//								src_gray_blur.data[i - src_gray_blur.cols] + 
	//								src_gray_blur.data[i + src_gray_blur.cols]
	//								) / 4;
	//	}
	//}

	for (size_t row = 1; row < src_gray_blur.rows-1; row++)
	{
		for (size_t col = 1; col < src_gray_blur.cols-1; col++)
		{
			int index = (row)*src_gray.cols + (col);
			if (src_gray_blur.data[index] < 5 || src_gray_blur.data[index] >250)
			{
				src_gray_blur.data[index] =(src_gray_blur.data[index - 1] +
											src_gray_blur.data[index + 1] +
											src_gray_blur.data[index - src_gray_blur.cols] +
											src_gray_blur.data[index + src_gray_blur.cols]
					) / 4;
			}
		}
	}



	return 1;
}