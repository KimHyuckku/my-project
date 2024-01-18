#include "Common.h"


void MatchingMethod(const Mat& serch_img, const Mat& ptrn_img, const double& thres, vector<Rect>& rois)
{
	/*
	uchar* pSearch = serch_img.data;
	int search_w = serch_img.cols;
	int search_h = serch_img.rows;
	uchar* pPtrn = ptrn_img.data;
	int ptrn_w = ptrn_img.cols;
	int ptrn_h = ptrn_img.rows;

	Mat result = Mat::zeros(Size(search_w - ptrn_w + 1, search_h - ptrn_h + 1), CV_32FC1);
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

			//matching_img.at<double>(row, col) = TM_SQDIFF;
			//if (TM_SQDIFF == 0)
			//	ptFind.push_back(Point(col, row));

			if (ptrnSQ == 0) ptrnSQ = 1;
			TM_SQDIFF_NORMED = TM_SQDIFF / sqrt(ptrnSQ * searchSQ);
			result.at<float>(row, col) = TM_SQDIFF_NORMED;
			//if (TM_SQDIFF_NORMED <= 0.009)
			//	rois.push_back(Rect(col, row, ptrn_w, ptrn_h));
		}
	}
	*/

	Mat result = Mat::zeros(Size(serch_img.cols - ptrn_img.cols + 1, serch_img.rows - ptrn_img.rows + 1), CV_32FC1);
	int match_method = TM_CCORR_NORMED;
	matchTemplate(serch_img, ptrn_img, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());


	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	bool multiobjects = true;
	if (!multiobjects)
	{
		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}

		rois.push_back(Rect(matchLoc.x, matchLoc.y, ptrn_img.cols, ptrn_img.rows));

	}
	else
	{
		Mat tm_bin;
		double min_thr = thres;
		double max_thr = 1.0;
		cv::threshold(result, tm_bin, min_thr, max_thr, ThresholdTypes::THRESH_BINARY);
		tm_bin *= 255;

		tm_bin.convertTo(tm_bin, CV_8UC1);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(tm_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		for (size_t i = 0; i < contours.size(); i++)
		{
			RotatedRect rrt = minAreaRect(contours[i]);
			//rois.push_back(rrt.boundingRect());
			rois.push_back(Rect(rrt.boundingRect().tl().x, rrt.boundingRect().tl().y, ptrn_img.cols, ptrn_img.rows));
		}
	}
}


void main()
{
	std::string filePath_Search = "../KCCImageNet/Willie/Willie.jpg";
	std::string filePath_Ptrn = "../KCCImageNet/Willie/me.jpg";

	cv::Mat src_draw = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_ANYCOLOR);
	cv::Mat src_gray_search = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src_gray_ptrn = cv::imread(filePath_Ptrn, cv::ImreadModes::IMREAD_GRAYSCALE);

	double thres = 0.99;
	vector<Rect> finds;
	MatchingMethod(src_gray_search, src_gray_ptrn, thres, finds);


	for (size_t k = 0; k < finds.size(); k++)
	{
		cv::rectangle(src_draw, finds[k], CV_RGB(255, 0, 0), 1);

		string msg;
		cv::drawMarker(src_draw, finds[k].tl(), CV_RGB(255, 0, 0), MarkerTypes::MARKER_CROSS);
		msg = to_string(k +1);
		putText(src_draw, msg, finds[k].tl(), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 0, 10), 1, 8);

	}
	int a = 0;
}