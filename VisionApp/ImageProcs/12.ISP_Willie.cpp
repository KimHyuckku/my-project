#pragma once
#include "ISP.h"

void getROIs(const Mat& serch_img, const Mat& ptrn_img, vector<Rect>& rois)
{
	uchar* pSearch = serch_img.data;
	int search_w = serch_img.cols;
	int search_h = serch_img.rows;
	uchar* pPtrn = ptrn_img.data;
	int ptrn_w = ptrn_img.cols;
	int ptrn_h = ptrn_img.rows;

	Mat tm_img = Mat::zeros(Size(search_w - ptrn_w + 1, search_h - ptrn_h + 1), CV_32FC1);
	for (size_t row = 0; row < search_h - ptrn_h + 1; row++)
	{
		for (size_t col = 0; col < search_w - ptrn_w + 1; col++)
		{
			double TM_SQDIFF = 0.0;
			double TM_SQDIFF_NORMED = 0.0;
			for (size_t prow = 0; prow < ptrn_h; prow++)
			{
				for (size_t pcol = 0; pcol < ptrn_w; pcol++)
				{
					int search_index = (row + prow) * search_w + (col + pcol);
					int ptrn_index = prow * ptrn_w + pcol;

					double diff = pSearch[search_index] - pPtrn[ptrn_index];
					TM_SQDIFF += (diff * diff);
				}
			}
			double ptrnSQ = 0., searchSQ = 0.;
			for (size_t prow = 0; prow < ptrn_h; prow++)
			{
				for (size_t pcol = 0; pcol < ptrn_w; pcol++)
				{
					int search_index = (row + prow) * search_w + (col + pcol);
					int ptrn_index = prow * ptrn_w + pcol;
					searchSQ += pSearch[search_index] * pSearch[search_index];
					ptrnSQ += pPtrn[ptrn_index] * pPtrn[ptrn_index];
				}
			}

			if (ptrnSQ == 0) ptrnSQ = 1;
			TM_SQDIFF_NORMED = TM_SQDIFF / sqrt(ptrnSQ * searchSQ);
			tm_img.at<float>(row, col) = TM_SQDIFF_NORMED;
			//if (TM_SQDIFF_NORMED <= 0.009)
			//	rois.push_back(Rect(col, row, ptrn_w, ptrn_h));
		}
	}
	Mat tm_bin;
	double min_thr = 0.8;
	double max_thr = 1.0;
	cv::threshold(tm_img, tm_bin, min_thr, max_thr, ThresholdTypes::THRESH_BINARY_INV);
	tm_bin *= 255;

	tm_bin.convertTo(tm_bin, CV_8UC1);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(tm_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rrt = minAreaRect(contours[i]);
		rois.push_back(rrt.boundingRect());
		//rois.push_back(Rect(rrt.center.x + offset_x, start_y, w, h));
	}

	int b = 0;
}


int main()
{
	std::string fileName_ptrn = "../KCCImageNet/Willie/me.jpg";
	std::string fileName = "../KCCImageNet/Willie/Willie.jpg";

	cv::Mat src_draw = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src_ptrn = cv::imread(fileName_ptrn, cv::ImreadModes::IMREAD_GRAYSCALE);

	uchar* pData = src_gray.data;
	size_t width = src_gray.cols;
	size_t height = src_gray.rows;
	uchar* pPtrn = src_ptrn.data;
	size_t Pwidth = src_ptrn.cols;
	size_t Pheight = src_ptrn.rows;

	std::vector<Rect> vROIs;
	getROIs(src_gray, src_ptrn, vROIs);


	int index=0;


	std::cout << "Àª¸®´Â " << index << " °³" << std::endl;



	return 1;
}