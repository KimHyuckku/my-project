#pragma once

#include "ISP.h"

int main()
{
	int datas[] = { 6,4,8,9,4,4,8,64,4,6,4,8,6,4,11,1,3,1134,5,64,5,64 };
	//노이즈가 없는 대표 신호 값을 정하시오.
	
	// 4, 6, 8
	int size = (sizeof(datas) / sizeof(datas[0]));
	int sum1=0;

	for (int i = 0; i <= size; i++)
	{
		if (datas[i] > 50)
		{
			size -= 1;
		}
		else sum1 += datas[i];
	}
	std::cout << size << std::endl;
	std::cout << sum1 << std::endl;
	double avg = sum1 / size;

	std::cout << "노이즈 없는 평균 : " << avg << std::endl;

	size = (sizeof(datas) / sizeof(datas[0]));
	std::sort(datas, datas + size);
	int major = datas[size / 2];
	std::cout << "중간값 : " << major << std::endl;


	/*
	std::vector<int> vDatas(datas, datas + size);
	std::sort(vDatas.begin(), vDatas.end());
	int major_v = vDatas[size / 2];
	*/


	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

cv:Mat src_gray_blur = src_gray.clone();
	src_gray_blur = 0;

	//filter 3*3 .... 1/9
	//
	const int filter_sz = 3;
	float blur[] = {
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9
	};
	int half_kernelSize = filter_sz / 2;
	for (size_t row = half_kernelSize; row < src_gray.rows - half_kernelSize; row++)
	{
		for (size_t col = half_kernelSize; col < src_gray.cols - half_kernelSize; col++)
		{
			int sum = 0;
			for (int f_row = -half_kernelSize; f_row <= half_kernelSize; f_row++)
			{
				for (int f_col = half_kernelSize; f_col <= half_kernelSize; f_col++)
				{
					int index = (row + f_row) * src_gray.cols + (col + f_col);
					int f_index = (f_row+half_kernelSize)*filter_sz + (f_col+ half_kernelSize);
					sum += src_gray.data[index] * blur[f_index];
				}
			}
			int index = (row)*src_gray.cols + (col);
			src_gray_blur.data[index] = static_cast<uchar>(sum);

		}
	}

	return 1;
}
