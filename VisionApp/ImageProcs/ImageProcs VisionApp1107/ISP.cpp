#include "ISP.h"

ISP::ISP()
{
	std::cout << "ISP::Ctor" << std::endl;
}

ISP::~ISP()
{
	std::cout << "ISP::Dtor" << std::endl;
}

bool ISP::Convert_BGR2GRAY(uchar* pBGR, int cols, int rows, uchar* pGray)
{
	if (pBGR == nullptr || pGray == nullptr)
	{
		return false;
	}

	Mat src = Mat(rows, cols, CV_8UC3, pBGR);
	Mat gray_cv = Mat(rows, cols, CV_8UC1, pGray);
	cvtColor(src, gray_cv, COLOR_BGR2GRAY);

	return true;


	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			int index = (row)*cols + (col);
			//Y←0.299⋅R+0.587⋅G+0.114⋅B
			float val_Y =
				0.299 * pBGR[index * 3 + 2]//r
				+ 0.587 * pBGR[index * 3 + 1]//g
				+ 0.114 * pBGR[index * 3 + 0];//b
			pGray[index] = (uchar)(val_Y + 0.5);

		}
	}

	return true;
}

bool ISP::Get_Histogram(uchar* pGray, int cols, int rows, int* pHisto, int histoSz)
{
	if (pGray == nullptr || pHisto == nullptr)
	{
		return false;
	}

	for (size_t i = 0; i < cols*rows; i++)
	{
		if (pGray[i] >= histoSz) continue; // size 256
		pHisto[pGray[i]]++;
	}

	return false;
}

bool ISP::Enhance_HistogramEq(uchar* pGray, int cols, int rows, uchar* pGrayEq)
{
	int length = cols * rows;
	const int histoSz = 256;
	int histo[histoSz] = { 0, };
	Get_Histogram(pGray, cols, rows, histo, histoSz);

	//확률밀도함수
	int acc[histoSz] = { 0, };
	//acc[0] = histo[0]+ histo[1]
	acc[0] = histo[0];
	for (size_t i = 1; i < histoSz; i++)
	{
		acc[i] = acc[i - 1]/*histo[i-1]*/ + histo[i];
	}

	//new Look Up Table ... 영상의 각 화소 값들을 새로운 대응값으로 맵핑
	int new_Gray[histoSz] = { 0, };
	for (size_t i = 0; i < histoSz; i++)
	{
		new_Gray[i] = static_cast<int>(1.0 * acc[i] * 255 / length);
	}


	for (size_t i = 0; i < length; i++)
	{
		pGrayEq[i] = new_Gray[pGray[i]];
	}

	return true;
}
