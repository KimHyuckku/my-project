#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);

	ISP _isp;

	//Gray Input
	Mat src_gray;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	//Gamma Correction
	//double normalized_value = (double)pixels[i] / 255.0;
	//double corrected_value = pow(normalized_value, gamma) * 255.0;
	double gamma = 1.2;
	Mat src_gamma = Mat(src.size(), CV_8UC1);
	for (size_t i = 0; i < src.total(); i++)
	{
		src_gamma.data[i] = static_cast<uchar>
			(std::pow(src_gray.data[i] / 255.0, gamma) * 255.0 + 0.5);
	}
	//Gray Output

	return 1;
}