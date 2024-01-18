#include <iostream>
#include <vector>
#include <string>

int main()
{
	std::vector<int> sosu = {2};
	int temp;
	for (int i = 3; i < 100000; i++)
	{
		int flag = 1;
		for (size_t j = 0; j < sosu.size(); j++)
		{
			if (i % sosu[j] == 0)
			{
				flag = 0;
				break;
			}

		}

		if (flag == 1)
		{
			sosu.push_back(i);
			std::cout << i << std::endl;
		}
	}

	std::cout << " 10000 미만의 소수 " << sosu.size() <<" 개" << std::endl;



	return 0;
}
