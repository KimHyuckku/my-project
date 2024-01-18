#include <iostream>


int main()
{
	const int length = 3 * 3;
	int datas[length] = { 5, 3, 1, 4, 6, 4, 8, 4, 3 };
	int counts[length] = { 0, };

	int _max_count_val = -1;
	int _min_count_val = 1000;

	for (size_t i = 0; i < length; i++)
	{
		counts[datas[i]]++;
		if (_max_count_val < counts[datas[i]]) _max_count_val = counts[datas[i]];
		if (_min_count_val > counts[datas[i]]) _min_count_val = counts[datas[i]];
	}

	for (size_t i = 0; i < length; i++)
	{
		if (_max_count_val == counts[i])
			std::cout << "가장 많은 빈도 값: " << i << " ... " << counts[i] << "개" << std::endl;
	}
	for (size_t i = 0; i < length; i++)
	{
		if (_min_count_val == counts[i])
			std::cout << "가장 많은 빈도 값: " << i << " ... " << counts[i] << "개" << std::endl;
	}

	//int data[3 * 3] = { 5, 3, 1, 4, 6, 4, 8, 4, 3 };
	//int data_index[sizeof(data)];
	//int i, j, top, top_index;

	//for (i = 0; i < sizeof(data); i++)
	//{
	//	data_index[i] = 0;
	//	for (j = 0; j < sizeof(data); j++)
	//	{

	//		if (data[i] == data[j])
	//		{
	//			data_index[i] += 1;
	//		}
	//	}
	//	if (data_index[i] > data_index[i - 1])
	//	{
	//		top = data[i];
	//		top_index = data_index[i];
	//	}
	//}
	//std::cout << sizeof(data) << std::endl;
	//std::cout << "가장 많은 빈도 값 : " << top << "..." << top_index << "개 \n";

	return 1;
}