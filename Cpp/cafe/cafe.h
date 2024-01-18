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
        "ī��_�Ƹ޸�ī�� Short",
        "ī��_�Ƹ޸�ī�� Tall",
        "ī�� �� Short",
        "ī��_�� Tall",
        "īǪġ�� Short",
        "īǪġ�� Tall",
        "ī���ī Short",
        "ī���ī Tall",
        "ī���_��Ű�߶� Short",
        "ī���_��Ű�߶� Tall",
        "��Ÿ����_��ü_�� Short",
        "��Ÿ����_��ü_�� Tall"
    };

    double menu_price[14] = { 0, 3.6, 4.1, 4.1, 4.6, 4.1, 4.6, 4.1, 4.6, 5.1, 5.6, 5.1, 5.6 };

    int total_price = 0;
    friend Cafe;

public:
    static int acc_price[14];
};

#endif