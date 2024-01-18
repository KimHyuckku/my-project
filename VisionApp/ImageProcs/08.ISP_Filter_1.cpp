#pragma once

#include "ISP.h"

int main()
{
	int datas[] = { 6,4,8,9,4,4,8,64,4,6,4,8,6,4,11,1,3,1134,5,64,5,64 };
	//노이즈가 없는 대표 신호 값을 정하시오.

	//4, 6, 8
	int size = sizeof(datas) / sizeof(datas[0]);
	std::sort(datas, datas + size);
	
	std::vector<int> vDatas(datas, datas + size);
	std::sort(vDatas.begin(), vDatas.end());

	int major = datas[size / 2];
	int major_v = vDatas[size / 2];


	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	cv::Mat src_gray_blur = src_gray.clone();
	src_gray_blur = 255;

	//filter 3x3 ... 1/9
	const int filter_sz = 3;
	/*float blur[] = {
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9, 
	};*/
	float blur[] = {
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16,
	};

	int half_kernelSize = filter_sz / 2;
	for (size_t row = half_kernelSize; row < src_gray.rows- half_kernelSize; row++)
	{
		for (size_t col = half_kernelSize; col < src_gray.cols- half_kernelSize; col++)
		{
			int sum = 0;
			for (int f_row = -half_kernelSize; f_row <= half_kernelSize; f_row++)
			{
				for (int f_col = -half_kernelSize; f_col <= half_kernelSize; f_col++)
				{
					int index = (row+ f_row) * src_gray.cols + (col+ f_col);
					int f_index = (f_row+ half_kernelSize)*filter_sz + (f_col+ half_kernelSize);
					sum += src_gray.data[index] * blur[f_index];
				}
			}
			int index = (row) * src_gray.cols + (col);
			src_gray_blur.data[index] = static_cast<uchar>(sum);
		}
	}
	
	for (size_t row = 0; row < src_gray_blur.rows; row++)
	{
		int index_0 = row * src_gray_blur.cols + 0;
		int index_1 = row * src_gray_blur.cols + 1;
		int index_2 = row * src_gray_blur.cols + (src_gray_blur.cols-1);
		int index_3 = row * src_gray_blur.cols + (src_gray_blur.cols-2);
		src_gray_blur.data[index_0] = src_gray_blur.data[index_1];
		src_gray_blur.data[index_2] = src_gray_blur.data[index_3];
	}

	for (size_t col = 0; col < src_gray.cols; col++)
	{
		int index_0 = col;
		int index_1 = col + src_gray.cols;
		int index_2 = col + src_gray_blur.rows * (src_gray.cols - 1) ;
		int index_3 = col + src_gray_blur.rows * (src_gray.cols - 2) ;
		src_gray_blur.data[index_0] = src_gray_blur.data[index_1];
		src_gray_blur.data[index_2] = src_gray_blur.data[index_3];
	}

	//src_gray_blur.rows*src_gray.cols + (col)
	src_gray_blur.data[0] = (src_gray_blur.data[0 + 1] +src_gray_blur.data[1 * src_gray_blur.cols + 0]) / 2;

	src_gray_blur.data[ 1 * src_gray_blur.cols-1] = (
								src_gray_blur.data[ 1 * src_gray_blur.cols - 2] 
							  + src_gray_blur.data[ 2 * src_gray_blur.cols - 1]
							) / 2;
	src_gray_blur.data[src_gray_blur.rows * (src_gray.cols-1)] = (
								src_gray_blur.data[src_gray_blur.rows * (src_gray.cols - 2)]
							  + src_gray_blur.data[src_gray_blur.rows * (src_gray.cols - 1) + 1]
							) / 2;

	src_gray_blur.data[src_gray.cols * src_gray_blur.rows - 1] = (
								src_gray_blur.data[src_gray_blur.rows * (src_gray.cols - 1) - 1]
							  + src_gray_blur.data[src_gray.rows * src_gray_blur.cols -2]
							) / 2;





	return 1;
}