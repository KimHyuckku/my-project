#include "cafe.h"

void Cafe::get_menu() {
    cafe_menu choose;

    cout << "========== CAFE MENU LIST==========\n";
    for (int i = 1; i < 13; i++)
    {
        cout << "[" << i << "]" << choose.menu_list[i] << " " << choose.menu_price[i] << "\n";
    }
}

void Cafe::menu_price(int sel) {
    cafe_menu choose;

    cout << choose.menu_list[sel] << " " << choose.menu_price[sel] * 1000 << "원\n";
    sum = sum + choose.menu_price[sel] * 1000;
}

void Cafe::total_cal() {
    cafe_menu choose;

    for (int i = 1; i < 13; i++)
    {
        if (choose.acc_price[i] > 0)
        {
            cout << choose.menu_list[i] << " " << choose.acc_price[i] << "\n";
            choose.total_price = choose.total_price + choose.acc_price[i] * choose.menu_price[i] * 1000;
        }
    }
    cout << "매출액 통계 : " << choose.total_price << "\n";
}

void Cafe::menu_num_up(int num) {
    cafe_menu ch;

    for (int i = 1; i < 13; i++)
    {
        if (num == i)
        {
            ch.acc_price[i] = ch.acc_price[i] + 1;
        }
    }
}

int cafe_menu::acc_price[14] = { 0 };