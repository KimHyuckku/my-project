#pragma once
#include "Common.h"

int main()
{
	std::string fileName = "../KCCImageNet/stinkbug.png";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::resize(src, src, cv::Size(src.cols * 2, src.rows * 2));
	int datas[10] = { 5,3,1,4,6,4,8,4,3 };
	int* pDatas = datas;//data array

	uchar* pData = src.data;//data array...start[0,1,2,3,4,5]
	int length = src.total();//data length
	int channels = src.channels();
	//length *= channels;




	const int histoSz = 256;//sizeof(uchar);
	int histo[histoSz] = { 0, };
	//int* pHisto = new int[length];
	
	for (size_t i = 0; i < length; i++)
	{
		histo[pData[i]]++;
	}

	uchar* data = src.data;
	int size = src.rows * src.cols;
	auto result = std::minmax_element(pData, pData + length);
	double mean_brightness = cv::mean(src)[0];
	auto _minmax = std::minmax_element(histo, histo + histoSz);
	int _min_value = *_minmax.first;
	int _max_value = *_minmax.second;


	std::string strLine;
	for (size_t row = 0; row < histoSz; row++)
	{
		strLine = "";
		strLine += to_string(row);
		strLine += ("   ||");

		int scaled_cols = (histo[row]*1.0 / _max_value) * 100;
		for (size_t col = 0; col < scaled_cols; col++)
		{
			strLine += ("=");
		}
		std::cout << strLine << std::endl;
	}

	cv::Mat draw = src.clone();
	cvtColor(draw, draw, ColorConversionCodes::COLOR_GRAY2BGR);
	for (size_t row = 0; row < histoSz; row++)
	{ 
		int scaled_cols = (histo[row] * 1.0 / _max_value) * src.cols;
		cv::Point st = Point(0, row*2.7);
		cv::Point ed = Point(scaled_cols, row*2.7);
		cv::line(draw, st, ed, CV_RGB(255, 255, 0));
	}

	int a = 0;



	//histogram을 구하시오. (src 이미지 버퍼)
	// 0   | =========== 10
	// 1   | ======= 5
	// 2   | ========== 8
	// ...
	// 255 | ================ 13






	if (false)
	{
		const int length = 3 * 3;
		int datas[length] = { 5,3,1,4,6,4,8,4,3 };
		int counts[length] = { 0, };
		//value...->...index
		int _max_count_val = -1;
		int _min_count_val = 1000;
		for (size_t i = 0; i < length; i++)
		{
			counts[datas[i]]++;
			if (_max_count_val < counts[datas[i]])_max_count_val = counts[datas[i]];
			if (_min_count_val > counts[datas[i]])_min_count_val = counts[datas[i]];
		}

		//display
		for (size_t i = 0; i < length; i++)
		{
			if (_max_count_val == counts[i])
				std::cout << "가장 많은 빈도 값 : " << i << " ... " << counts[i] << "개" << std::endl;
		}
		for (size_t i = 0; i < length; i++)
		{
			if (_min_count_val == counts[i])
				std::cout << "가장 적은 빈도 값 : " << i << " ... " << counts[i] << "개" << std::endl;
		}


		//Quiz :: 가장 많은/적은 빈도수의 값을 출력하시오
		//Answer
		//가장 많은 빈도 값 : 4 ... 3개
		//가장 적은 빈도 값 : 1 ... 1개
		//                   5 ... 1개
		//                   8 ... 1개
	}

	
	return 1;
}
