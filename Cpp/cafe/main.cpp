#include <iostream>
#include "cafe.h"
using namespace std;

int main()
{
    int i;
    cafe_menu select;
    Cafe show;

    int menu_select[14];

    show.get_menu();

    while (1)
    {
        cout << "\n>>";

        for (i = 1; i < 13; i++)
        {
            cin >> menu_select[i];

            show.menu_num_up(menu_select[i]);

            if (menu_select[1] == 0)    // 0 ������ ���� ġ�� �������� �Ѿ�� ��
            {
                cout << "==========���� ���==========\n";
                show.total_cal();
                break;
            }
            else if (menu_select[i] < 0 || menu_select[i]>12)
            {
                cout << menu_select[i] << "�� ���� �޴��Դϴ�...\n";
                break;
            }
            else if (menu_select[i] == 0)
            {
                cout << "�ֹ��� ��ǰ : \n";
                for (int j = 1; j < i; j++)
                {
                    show.menu_price(menu_select[j]);
                }
                cout << "�հ� : " << show.sum << "\n";
                show.sum = 0;
                fill_n(menu_select, 14, -1);
                /*delete [] menu_select;*/
                break;
            }
        }
    }
}