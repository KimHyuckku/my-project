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
	//std::string filePath_Search = "../KCCImageNet/solar_cell/solar_cell_05.png";
	std::string filePath_Ptrn = "../KCCImageNet/solar_cell/solar_cell_ptrn3.bmp";
	int img_counts = 10;
	for (size_t img_index = 1; img_index <= img_counts; img_index++)
	{
		std::string filePath_Search = "../KCCImageNet/solar_cell/solar_cell_" + std::format("{:02d}.png", img_index);


		cv::Mat src_draw = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_ANYCOLOR);
		cv::Mat src_gray_search = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_GRAYSCALE);
		cv::Mat src_gray_ptrn = cv::imread(filePath_Ptrn, cv::ImreadModes::IMREAD_GRAYSCALE);

		Mat src_color = src_draw.clone();

		Mat src_bgr[3];
		cv::split(src_color, src_bgr);
		Mat src_gray = src_bgr[2];//red channel

		Mat src_cell_region;
		double thres_region = 159;
		threshold(src_gray, src_cell_region,
			thres_region, 255, ThresholdTypes::THRESH_BINARY_INV);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(src_cell_region, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		Mat defect_regions = Mat::zeros(src_color.size(), CV_8UC1);
		for (size_t i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[i]);
			if (area > 100000) continue;
			if (area < 1000) continue;
			drawContours(defect_regions, contours, i, CV_RGB(255, 255, 255), LineTypes::FILLED);
		}

		if (true)//dis-connected area
		{
			contours.clear();
			hierarchy.clear();
			findContours(defect_regions, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

			vector<Rect> vDefectRegions;
			for (size_t i = 0; i < contours.size(); i++)
			{
				RotatedRect rrt = minAreaRect(contours[i]);
				int deflate = 10;
				Rect rt = Rect(rrt.boundingRect().x + deflate,
					rrt.boundingRect().y + deflate,
					rrt.boundingRect().width - deflate * 2,
					rrt.boundingRect().height - deflate * 2);
				if (rt.width < 10 || rt.height < 10)continue;
				vDefectRegions.push_back(rt);
			}

			bool findError = false;
			for (size_t i = 0; i < vDefectRegions.size(); i++)
			{
				Rect rt = vDefectRegions[i];
				Mat subDefectRgn = ~defect_regions(rt).clone();
				Mat subDefectRgnFilled = subDefectRgn.clone();
				{
					contours.clear();
					hierarchy.clear();
					findContours(subDefectRgn, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					int y_min = 0;
					int y_max = 0;
					for (size_t i = 0; i < contours.size(); i++)
					{
						int _min = minAreaRect(contours[i]).boundingRect().y;
						int _max = y_min + minAreaRect(contours[i]).boundingRect().height;
						if (y_min < _min) y_min = _min;
						if (y_max < _max) y_max = _max;
					}
					for (size_t i = 0; i < contours.size(); i++)
					{
						RotatedRect rrt = minAreaRect(contours[i]);
						Rect rt = Rect(rrt.boundingRect().x, y_min, rrt.boundingRect().width, y_max - y_min);
						cv::rectangle(subDefectRgn, rt, CV_RGB(255, 255, 255), LineTypes::FILLED);

						Rect rt_filled = Rect(0, y_min, subDefectRgnFilled.cols, y_max - y_min);
						cv::rectangle(subDefectRgnFilled, rt_filled, CV_RGB(255, 255, 255), LineTypes::FILLED);

					}
				}

				Mat diff = subDefectRgnFilled - subDefectRgn;
				contours.clear();
				hierarchy.clear();
				findContours(diff, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);


				for (size_t i = 0; i < contours.size(); i++)
				{
					RotatedRect rrt = minAreaRect(contours[i]);
					cv::circle(src_draw, Point(rrt.center.x + rt.x, rrt.center.y + rt.y),
						10, CV_RGB(0, 255, 255), 2);

					ostringstream ss;
					ss << std::fixed;
					ss << "[";
					ss << to_string(i + 1);
					ss << "]";
					ss << " x = ";
					ss << std::setprecision(3) << rrt.center.x + rt.x;
					ss << " y = ";
					ss << std::setprecision(3) << rrt.center.y + rt.y;
					string ssTxt = ss.str();
					//AddString(ssTxt.c_str());
					std::cout << ssTxt.c_str() << std::endl;
					findError = true;
				}
			}

			if (findError)
			{
				//AddString("Found DisConnected Area");
				std::cout << "Found DisConnected Area" << std::endl;
			}
			else
			{
				//AddString("No DisConnected Area");
				std::cout << "No DisConnected Area" << std::endl;
			}
		}




		int a = 0;
	}

}