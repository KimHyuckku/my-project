#include "circle.h"
#include <iostream> 
using namespace std;

int Car::getCharge() {
	int charged_time;

	charged_time = car_out_hr * 60 + car_out_min - car_in_hr * 60 - car_in_min;

	if ((60 + car_out_min - car_in_min) % 10 == 0)
	{
		return charged_time / 30 * 1000 + (charged_time % 30) / 10 * 400;
	}
	else
	{
		return charged_time / 30 * 1000 + (charged_time % 30) / 10 * 400; +400;
	}
}

int Car::handed(int hand, int charge) {
	if (hand == 1)
	{
		charge = charge / 2;
	}

	return charge;
}

//// Clrcle Ŭ���� ����. ��� ��� �Լ��� �ۼ��Ѵ�.
//Circle::Circle() {
//	radius = 1;
//	cout << "������ " << radius << " �� ����\n";
//}
//
//Circle::Circle(int r) {
//	radius = r;
//	cout << "������ " << radius << " �� ����\n";
//}
//
//double Circle::getArea() {
//	return 3.14 * radius * radius;
//}
