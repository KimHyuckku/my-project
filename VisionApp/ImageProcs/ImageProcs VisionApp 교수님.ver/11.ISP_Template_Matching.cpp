#pragma once

#include "Common.h"

void main()
{
	string inString = "Kdfjow_Abcd_Abcd_Abcd_dkfjow";
	string Ptrn = "Abcd";
	//ptrn의 개수
	//ptrn의 인덱스
	//출력하시오
	std::vector<int> ptrn_pos;
	for (size_t i = 0; i < inString.length()-Ptrn.length(); i++)
	{
		int find = 0;
		for (size_t p = 0; p < Ptrn.length(); p++)
		{
			if (inString[i + p] - Ptrn[p] == 0)
			{
				find ++;
			}
		}
		if (find == Ptrn.length())
		{
			ptrn_pos.push_back(i);
		}
	}
	std::cout << "ptrn의 개수 : " << ptrn_pos.size() << std::endl;
	std::cout << "ptrn의 인덱스 : ";
	for (size_t i = 0; i < ptrn_pos.size(); i++)
	{
		std::cout << ptrn_pos[i] << ", ";
	}
	std::cout << std::endl;
	int a = 0;
}
