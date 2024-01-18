#pragma once

#include "Common.h"


void main()
{
	string inString = "kdfjow_Abcd_Abcd_Abcd_dkfjow";
	string Ptrn = "Abcd";

	int temp1, temp2=0, index=0;
	// ptrn의 개수
	// ptrn의 인덱스
	// 출력하시오
		
	for (size_t i = 0; i < inString.size()-3; i++)
	{
		if (inString[i] == Ptrn[0])
		{
			for (size_t j = 1; j < Ptrn.size(); j++)
			{
				temp1 = inString[i + j] - Ptrn[j];
				temp2 += temp1;
			}
			if (temp2 == 0) index++;

		}
	}

	std::cout << "Ptrn의 갯수는 "<< index << " 개" << std::endl;

	int a = 0;
}
