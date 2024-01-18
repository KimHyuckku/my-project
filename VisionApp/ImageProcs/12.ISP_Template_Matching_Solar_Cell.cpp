#include "Common.h"


void MatchingMethod(const Mat& serch_img, const Mat& ptrn_img, const double& thres, vector<Rect>& rois)
{
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
	std::string filePath_Search = "../KCCImageNet/solar_cell/solar_cell_10.png";
	std::string filePath_Ptrn = "../KCCImageNet/solar_cell/solar_cell_ptrn3.bmp";

	cv::Mat src_draw = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_ANYCOLOR);
	cv::Mat src_gray_search = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src_gray_ptrn = cv::imread(filePath_Ptrn, cv::ImreadModes::IMREAD_GRAYSCALE);

	cv::Mat src_channels[3];
	cv::split(src_draw, src_channels);
	cv::Mat src_r = src_channels[2];

	cv::Mat src_bin= src_r.clone();
	uchar* pData = src_r.data;
	uchar* pDataBin = src_bin.data;

	int threshold_min = 150;
	int threshold_max = 255;
	cv::threshold(src_r, src_bin, threshold_min, threshold_max, ThresholdTypes::THRESH_BINARY_INV);

	int kernerSz = 1;
	int shape = MorphShapes::MORPH_RECT;
	cv::Size sz = Size(2 * kernerSz + 1, 2 * kernerSz + 1);
	Mat SE = cv::getStructuringElement(shape, sz);

	Mat src_bin_open;
	int type = MorphTypes::MORPH_OPEN;
	cv::morphologyEx(src_bin, src_bin_open, type, SE);

	RNG rng(12345);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<cv::Rect> vAbnormalRegions;

	double per = 0.1;
	double avg_height = 21;
	double spec_height_min = avg_height - avg_height * per;
	double spec_height_max = avg_height + avg_height * per;

	findContours(src_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		RotatedRect rrt = minAreaRect(contours[i]);
		double contours_height = rrt.boundingRect().height;

		double area = contourArea(contours[i]);
		if (area > 100000) continue;

		if (contours_height > spec_height_max)
		{
			cv::Rect region = rrt.boundingRect();
			cv::rectangle(src_draw, region, CV_RGB(255, 255, 0),1);
			cv::Mat subRegion = src_r(region);
			cv::Mat subRegion_bin = subRegion.clone();

			uchar* subData = subRegion.data;
			uchar* subDataBin = subRegion_bin.data;

			cv::threshold(subRegion, subRegion_bin, threshold_min, threshold_max, ThresholdTypes::THRESH_BINARY);

			int hole_sz = 200;
			int hole_length = 0;
			int hole_right = 0;
			int sum = 0;
			int index = 0;

			for (size_t j = 1; j < (contours_height + avg_height / 2) / avg_height - 1; j++)
			{



				for (size_t col = 1; col < subRegion.cols - 1; col++)
				{
					for (size_t row = avg_height*j - 2; row <= avg_height*j + 2; row++)
					{
						int value = subDataBin[row * subRegion.cols + col];
						sum += value;
					}

					if (sum < hole_sz)
					{
						hole_right = col;
						hole_length++;
					}
					else
					{
						if (hole_length > 0)
						{
							int radius = 7;
							Point cir_ctr = Point(rrt.boundingRect().tl().x + hole_right - hole_length / 2,
								rrt.boundingRect().tl().y + avg_height*j);
							cv::circle(src_draw, cir_ctr, radius, CV_RGB(255, 0, 0), 2);
							hole_length = 0;
						}
						sum = 0;
					}
				}
			}

			int b = 0;
		}
	}


	double thres = 0.97;
	vector<Rect> finds;
	MatchingMethod(src_bin_open, src_gray_ptrn, thres, finds);
	for (size_t k = 0; k < finds.size(); k++)
	{
		cv::circle(src_draw, Point(finds[k].x+2, finds[k].y+2), 5,  CV_RGB(255, 0, 0), 2);
		string msg;
		msg = to_string(k +1);
		putText(src_draw, msg, finds[k].tl(), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 255, 10), 1, 8);
	}
	
	int a = 0;
}