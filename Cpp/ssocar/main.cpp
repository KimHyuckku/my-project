#include "ssocar.h"
#include <iostream>
using namespace std;


int main()
{
	int c_num, in_time_hr, in_time_min, out_time_hr, out_time_min, loc, car_handed, money, handed_charge;
	int i = 0;
	Car morning[10];

	while (1)
	{
		cout << "�� ��ȣ 4�ڸ��� �Է��ϼ��� : ";
		cin >> c_num;

		cout << "���� �ð��� �Է��ϼ���(��-07 50) : ";
		cin >> in_time_hr >> in_time_min;

		cout << "���� �ð��� �Է��ϼ���(��-14 30) : ";
		cin >> out_time_hr >> out_time_min;

		cout << "���� ��ġ�� �Է��ϼ��� : ";
		cin >> loc;

		cout << "����� ���� ������ �Է��ϼ��� (������̸� 1, �ƴϸ� 0): ";
		cin >> car_handed;

		morning[i].set_car_num(c_num);
		morning[i].set_time(in_time_hr, in_time_min, out_time_hr, out_time_min);
		morning[i].set_loc(loc);

		//money = morning[i].getCharge();
		//handed_charge = morning[i].handed(car_handed, morning[i].getCharge());

		morning[i].handed(car_handed, morning[i].getCharge());

		cout << "���� ����� " << morning[i].handed(car_handed, morning[i].getCharge()) << endl;

		i++;
		if (loc < 0)
			break;
	}



}