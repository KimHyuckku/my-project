#pragma once
#ifndef _CAFE_H_
#define _CAFE_H_

#include <iostream>
using namespace std;

class Cafe {
private:

public:
    int sum = 0;
    void get_menu();
    void menu_price(int sel);
    void total_cal();
    void menu_num_up(int num);
};

class cafe_menu {
private:
    string menu_list[14] = {
        "",
        "카페_아메리카노 Short",
        "카페_아메리카노 Tall",
        "카페 라떼 Short",
        "카페_라떼 Tall",
        "카푸치노 Short",
        "카푸치노 Tall",
        "카페모카 Short",
        "카페모카 Tall",
        "카라멜_마키야또 Short",
        "카라멜_마키야또 Tall",
        "스타벅스_돌체_라떼 Short",
        "스타벅스_돌체_라떼 Tall"
    };

    double menu_price[14] = { 0, 3.6, 4.1, 4.1, 4.6, 4.1, 4.6, 4.1, 4.6, 5.1, 5.6, 5.1, 5.6 };

    int total_price = 0;
    friend Cafe;

public:
    static int acc_price[14];
};

#endif