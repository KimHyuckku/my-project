#include "Braille_Def.h"

void get_bin_data(const Mat& img_gray, vector<vector<int>>& rois);// img와 img_gray에서 binary 데이터를 추출해 rois 벡터에 집어넣는데
void add_sts(map<string, vector<string>>& koreanBrailleMap, string letter, string letter_n, string letter_b, string& sts, int& flag);

int main()
{
	setlocale(LC_CTYPE, "");

	map<string, int> hangeul_cho;
	map<string, int> hangeul_jung;
	map<string, int> hangeul_jong;
	init_cho(hangeul_cho);
	init_jung(hangeul_jung);
	init_jong(hangeul_jong);

	/*int img_counts = 10;
	for (size_t img_index = 1; img_index <= img_counts; img_index++)
	{
		std::string filePath_Search = "../KCCImageNet/egukga" + std::format("{:d}.png", img_index);*/


		std::string filePath_Search = "../KCCImageNet/egukga1.png";
		cv::Mat src_draw = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_ANYCOLOR);
		cv::Mat src_draw_gray = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_GRAYSCALE);

		vector<vector<int> > sr_sts;
		vector<vector<int> > or_sts;
		string sentence;

		get_bin_data(src_draw_gray, sr_sts);

		map<string, vector<string>> koreanBrailleMap;
		brailleInit(koreanBrailleMap);

		stringstream result, result2;
		string letter, letter_n, letter_b = ("");
		int flag = 1;
		int word_count = sr_sts.size();
		vector<int> aaa;
		aaa.push_back(8);
		sr_sts.push_back(aaa);	//맨 뒷글자 확인용

		for (size_t i = 0; i < word_count; i++)
		{
			result.str("");
			result2.str("");
			copy(sr_sts[i].begin(), sr_sts[i].end(), std::ostream_iterator<int>(result, ""));
			copy(sr_sts[i + 1].begin(), sr_sts[i + 1].end(), std::ostream_iterator<int>(result2, ""));
			letter = result.str();
			letter_n = result2.str();	// 2개짜리 단어일 경우 확인하기 위한 다음 단어

			if (flag == 1)	// 2개짜리 단어가 있을 경우 하나를 스킵하기 위함
			{
				//예외 구분 함수
				add_sts(koreanBrailleMap, letter, letter_n, letter_b, sentence, flag);
				int k = 0;
			}
			else
			{
				flag = 1;
				continue;
			}

			letter_b = letter;
		}

		cout << sentence << endl;

		//----- 문자열구분
		wstring sentece_w;
		sentence += "       ";
		queue<string>q;
		map<string, int> findjung;
		init_jung(findjung);
		for (int i = 0; i < sentence.length() - 7; i += 2)
		{
			string ch1, ch2, ch3;
			if (sentence[i] != ' ')
			{
				string st = sentence.substr(i, 2);
				q.push(st);
				auto it = findjung.find(st);
				if (q.size() == 1 && it != findjung.end())
				{
					q.pop();
					q.push("ㅇ");
					q.push(st);
				}
				else;
				if (q.size() == 2 && sentence[i + 4] == ',')
				{
					ch1 = q.front();
					ch2 = q.back();
					ch3 = sentence.substr(i + 2, 2);
					if (sentence[i + 7] == ',')
					{
						string tmp = sentence.substr(i + 5, 2);
						ch3 += tmp;
						i += 3;
					}
					sentece_w.push_back(combine_hangul(ch1, ch2, ch3));
					while (!q.empty())q.pop();
					i += 3;
				}
				else if (q.size() == 2 && sentence[i + 4] != ',')
				{
					ch1 = q.front();
					ch2 = q.back();
					sentece_w.push_back(combine_hangul(ch1, ch2, ch3));
					while (!q.empty())q.pop();
				}
			}
			else
			{
				cout << " ";
				i--;
			}
		}
		cout << "\n";
		SpeakText(sentece_w.c_str());
	/*}*/
	int a = 0;
}

void get_bin_data(const Mat& img_gray, vector<vector<int>>& rois)
{
	cv::Mat bin;
	threshold(img_gray, bin, 200, 255, THRESH_BINARY);

	vector<vector<Point> > contours; //전체 객체 윤곽을 벡터 포인터로 벡터 내부에 저장
	vector<Vec4i> hierarchy;
	findContours(bin, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<int> center_x, center_y, btm_x, cut_line;
	int sum_area = 0;

	// 점자의 중심 좌표를 구해서 center 벡터에 넣는다
	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rrt = minAreaRect(contours[i]);
		int area = contourArea(contours[i]);
		center_x.push_back(rrt.center.x);
		center_y.push_back(rrt.center.y);
		sum_area += area;
		cv::drawMarker(bin, Point(rrt.center.x, rrt.center.y), 0, MarkerTypes::MARKER_CROSS,1,1);
	}
	int avg_area = sum_area / contours.size();

	int err = 2;
	for (size_t i = 1; i <= center_x.size(); i++)
	{
		if (center_y[i] > center_y[i - 1] - err && center_y[i] < center_y[i - 1] + err)
		{
			btm_x.push_back(center_x[i - 1]);
		}
		else
		{
			btm_x.push_back(center_x[i - 1]);
			break;
		}
	}

	sort(btm_x.begin(), btm_x.end());
	int l_btw_jum = img_gray.rows;
	for (size_t i = 0; i < btm_x.size() - 1; i++)
	{
		int diff;
		diff = abs(btm_x[i] - btm_x[i + 1]);

		if (diff < l_btw_jum && diff > err)
		{
			l_btw_jum = diff;
		}
	}

	for (size_t i = 0; i < btm_x.size() - 1; i++)
	{
		int diff;
		diff = abs(btm_x[i] - btm_x[i + 1]);

		if (diff > l_btw_jum + 1)
		{
			cut_line.push_back((btm_x[i] + btm_x[i + 1]) / 2);
		}
	}
	for (size_t i = 0; i <= cut_line.size(); i++)
	{
		Mat subRegion1, subRegion2;
		if (i == 0)
		{
			int temp;
			if (cut_line[i] - l_btw_jum * 2.5 < 0)
			{
				temp = 0;
			}
			else
			{
				temp = cut_line[i] - l_btw_jum * 2.5;
			}
			Rect region1 = Rect(Point(temp, 0), Point((cut_line[i] + temp) / 2, bin.rows));
			Rect region2 = Rect(Point((cut_line[i] + temp) / 2, 0), Point(cut_line[i], bin.rows));
			subRegion1 = bin(region1);
			subRegion2 = bin(region2);
		}
		else if (i == cut_line.size())
		{
			Rect region1 = Rect(Point(cut_line[i - 1], 0),
				Point(cut_line[i - 1] + l_btw_jum * 1.25, bin.rows));
			Rect region2 = Rect(Point(cut_line[i - 1] + l_btw_jum * 1.25, 0),
				Point(cut_line[i - 1] + l_btw_jum * 2.5, bin.rows));
			subRegion1 = bin(region1);
			subRegion2 = bin(region2);
		}
		else
		{
			Rect region1 = Rect(Point(cut_line[i - 1], 0),
				Point((cut_line[i - 1] + cut_line[i]) / 2, bin.rows));
			Rect region2 = Rect(Point((cut_line[i - 1] + cut_line[i]) / 2, 0),
				Point(cut_line[i], bin.rows));
			subRegion1 = bin(region1);
			subRegion2 = bin(region2);
		}

		vector<int> word_data;
		vector<vector<Point> > contours1;
		vector<Vec4i> hierarchy1;
		findContours(subRegion1, contours1, hierarchy1, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		for (size_t i = 0; i < contours1.size(); i++)
		{
			int area = contourArea(contours1[contours1.size() - i - 1]);
			int temp = 0;
			if (area > avg_area)
			{
				temp = 1;
			}
			word_data.push_back(temp);
		}

		vector<vector<Point> > contours2;
		vector<Vec4i> hierarchy2;
		findContours(subRegion2, contours2, hierarchy2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		for (size_t i = 0; i < contours2.size(); i++)
		{
			int area = contourArea(contours2[contours2.size() - i - 1]);
			int temp = 0;
			if (area > avg_area)
			{
				temp = 1;
			}
			word_data.push_back(temp);
		}
		rois.push_back(word_data);

		int a = 9;
	}
}

void add_sts(map<string, vector<string>>& koreanBrailleMap, string letter, 
				string letter_n, string letter_b, string& sts, int& flag)
{
	map<string, vector<string>> BrailleEx;
	brailleExceptionInit(BrailleEx);
	string str = "111010";
	if (koreanBrailleMap[letter].size() > 1)
	{
		int index = 0, i = 0;
		div_exc_index(letter, index);

		switch (index)
		{
		case 1:		// 것
			sts += *(BrailleEx[letter].data());
			flag = 0;
			break;
		case 2:		// ㅆ,ㅖ
			check_moum_b(letter_b, i);
			sts += *(BrailleEx[letter].data() + i);
			break;
		case 3:		// ㅅㄲㄸㅆㅉㅃ
			check_doinsori(letter_n, i, flag);
			sts += *(BrailleEx[letter].data() + i);
			break;
		case 4:		//ㅑㅘㅝㅜ
			if (letter_n == str)
			{
				sts += *(BrailleEx[letter].data() + 1);
				flag = 0;
			}
			else
			{
				sts += *BrailleEx[letter].data();
			}
			break;
		case 5:		// ㄴㄷㅁㅂㅈㅋㅌㅍㅎ
			check_moum_n(letter_n, i);
			sts += *(BrailleEx[letter].data() + i);
			break;
		default:
			std::cout << "Noting happened" << endl;
			break;
		}
	}
	else
	{
		sts += *(koreanBrailleMap[letter].data());
	}
}