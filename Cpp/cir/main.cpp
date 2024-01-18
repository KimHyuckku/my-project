#if 1
#include "circle.h"
#include <iostream>
using namespace std;


int main()
{
	int c_num, in_time_hr, in_time_min, out_time_hr, out_time_min, loc, car_handed, money, handed_charge;
	int i = 0;
	Car morning[10];

	while (1)
	{
		cout << "차 번호 4자리를 입력하세요 : ";
		cin >> c_num;

		cout << "배차 시간을 입력하세요(예-07 50) : ";
		cin >> in_time_hr >> in_time_min;

		cout << "출차 시간을 입력하세요(예-14 30) : ";
		cin >> out_time_hr >> out_time_min;

		cout << "배차 위치를 입력하세요 : ";
		cin >> loc;

		cout << "장애인 차량 유무를 입력하세요 (장애인이면 1, 아니면 0): ";
		cin >> car_handed;

		morning[i].set_car_num(c_num);
		morning[i].set_time(in_time_hr, in_time_min, out_time_hr, out_time_min);
		morning[i].set_loc(loc);

		//money = morning[i].getCharge();
		//handed_charge = morning[i].handed(car_handed, morning[i].getCharge());

		morning[i].handed(car_handed, morning[i].getCharge());

		cout << "주차 요금은 " << morning[i].handed(car_handed, morning[i].getCharge()) << endl;

		i++;
		if (loc < 0)
			break;
	}



}
#endif

#if 0
#include <iostream>
using namespace std;

int main()
{
	int n, i, j;
	cout << "입력할 정수의 갯수 : ";
	cin >> n;

	if (n <= 0) cout << "제대로된 갯수를 입력하시오.";

	int* p = new int[n];
	for (i = 0; i < n; i++)
	{
		cout << i+1 << " 번째 정수 : ";
		cin >> p[i];
	}
	
	int sum=0;
	for (i = 0; i < n; i++)
	{
		sum = sum + p[i];
	}
	
	cout << "평균 : "<< sum/n ;

}

#endif

#if 0
#include <iostream> 
using namespace std;

#include "circle.h"

int main() {
	Circle donut;
	double area = donut.getArea();
	cout << " donut의 면적은 " << area << "\n";

	Circle pizza(30);
	area = pizza.getArea();
	cout << "pizza의 면적은 " << area << "\n";
}
#endif


#if 0				// test용
#include <iostream>
using namespace std;

int main()
{
	int a, b;

	cout << "숫자 두개 입력 : ";
	cin >> a >> b;

	cout << a << ' ' << b;


}

#endif