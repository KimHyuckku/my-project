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

//// Clrcle 클래스 구현. 모든 멤버 함수를 작성한다.
//Circle::Circle() {
//	radius = 1;
//	cout << "반지름 " << radius << " 원 생성\n";
//}
//
//Circle::Circle(int r) {
//	radius = r;
//	cout << "반지름 " << radius << " 원 생성\n";
//}
//
//double Circle::getArea() {
//	return 3.14 * radius * radius;
//}
