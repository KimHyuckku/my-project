#pragma once
#ifndef SSOCAR_H
#define SSOCAR_H
#include <iostream>
using namespace std;

class Car {
private:
	int car_number;
	int car_in_hr;
	int car_in_min;
	int car_out_hr;
	int car_out_min;
	int car_loc;
	int car_handed;

	char client_account;

public:
	void set_car_num(int num) { car_number = num; }
	void set_time(int in_hr, int in_min, int out_hr, int out_min)
	{
		car_in_hr = in_hr; car_in_min = in_min; car_out_hr = out_hr; car_out_min = out_min;
	}
	void set_loc(int loc) { car_loc = loc; }
	int getCharge();

	int handed(int hand, int charge);
};


class LentCar : public Car {
private:
	

public:
	
};

#endif