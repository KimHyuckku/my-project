#pragma once

#include "Common.h"

void SpeakText(const wchar_t* text) {
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    ISpVoice* pVoice = NULL;
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);

    if (SUCCEEDED(hr)) {
        pVoice->Speak(text, 0, NULL);
        pVoice->WaitUntilDone(INFINITE);
        pVoice->Release();
    }

    CoUninitialize();
}


void init_cho(map<string, int>& hangeul_cho)
{
    hangeul_cho.insert(pair<string, int>("��", 0));
    hangeul_cho.insert(pair<string, int>("��", 1));
    hangeul_cho.insert(pair<string, int>("��", 2));
    hangeul_cho.insert(pair<string, int>("��", 3));
    hangeul_cho.insert(pair<string, int>("��", 4));
    hangeul_cho.insert(pair<string, int>("��", 5));
    hangeul_cho.insert(pair<string, int>("��", 6));
    hangeul_cho.insert(pair<string, int>("��", 7));
    hangeul_cho.insert(pair<string, int>("��", 8));
    hangeul_cho.insert(pair<string, int>("��", 9));
    hangeul_cho.insert(pair<string, int>("��", 10));
    hangeul_cho.insert(pair<string, int>("��", 11));
    hangeul_cho.insert(pair<string, int>("��", 12));
    hangeul_cho.insert(pair<string, int>("��", 13));
    hangeul_cho.insert(pair<string, int>("��", 14));
    hangeul_cho.insert(pair<string, int>("��", 15));
    hangeul_cho.insert(pair<string, int>("��", 16));
    hangeul_cho.insert(pair<string, int>("��", 17));
    hangeul_cho.insert(pair<string, int>("��", 18));
}

void init_jung(map<string, int>& hangeul_jung)
{
    hangeul_jung.insert(pair<string, int>("��", 0));
    hangeul_jung.insert(pair<string, int>("��", 1));
    hangeul_jung.insert(pair<string, int>("��", 2));
    hangeul_jung.insert(pair<string, int>("��", 3));
    hangeul_jung.insert(pair<string, int>("��", 4));
    hangeul_jung.insert(pair<string, int>("��", 5));
    hangeul_jung.insert(pair<string, int>("��", 6));
    hangeul_jung.insert(pair<string, int>("��", 7));
    hangeul_jung.insert(pair<string, int>("��", 8));
    hangeul_jung.insert(pair<string, int>("��", 9));
    hangeul_jung.insert(pair<string, int>("��", 10));
    hangeul_jung.insert(pair<string, int>("��", 11));
    hangeul_jung.insert(pair<string, int>("��", 12));
    hangeul_jung.insert(pair<string, int>("��", 13));
    hangeul_jung.insert(pair<string, int>("��", 14));
    hangeul_jung.insert(pair<string, int>("��", 15));
    hangeul_jung.insert(pair<string, int>("��", 16));
    hangeul_jung.insert(pair<string, int>("��", 17));
    hangeul_jung.insert(pair<string, int>("��", 18));
    hangeul_jung.insert(pair<string, int>("��", 19));
    hangeul_jung.insert(pair<string, int>("��", 20));
}

void init_jong(map<string, int>& hangeul_jong)
{
    hangeul_jong.insert(pair<string, int>("x", 0));
    hangeul_jong.insert(pair<string, int>("��", 1));
    hangeul_jong.insert(pair<string, int>("��", 2));
    hangeul_jong.insert(pair<string, int>("����", 3));
    hangeul_jong.insert(pair<string, int>("��", 4));
    hangeul_jong.insert(pair<string, int>("����", 5));
    hangeul_jong.insert(pair<string, int>("����", 6));
    hangeul_jong.insert(pair<string, int>("��", 7));
    hangeul_jong.insert(pair<string, int>("��", 8));
    hangeul_jong.insert(pair<string, int>("����", 9));
    hangeul_jong.insert(pair<string, int>("����", 10));
    hangeul_jong.insert(pair<string, int>("����", 11));
    hangeul_jong.insert(pair<string, int>("����", 12));
    hangeul_jong.insert(pair<string, int>("����", 13));
    hangeul_jong.insert(pair<string, int>("����", 14));
    hangeul_jong.insert(pair<string, int>("����", 15));
    hangeul_jong.insert(pair<string, int>("��", 16));
    hangeul_jong.insert(pair<string, int>("��", 17));
    hangeul_jong.insert(pair<string, int>("����", 18));
    hangeul_jong.insert(pair<string, int>("��", 19));
    hangeul_jong.insert(pair<string, int>("��", 20));
    hangeul_jong.insert(pair<string, int>("��", 21));
    hangeul_jong.insert(pair<string, int>("��", 22));
    hangeul_jong.insert(pair<string, int>("��", 23));
    hangeul_jong.insert(pair<string, int>("��", 24));
    hangeul_jong.insert(pair<string, int>("��", 25));
    hangeul_jong.insert(pair<string, int>("��", 26));
    hangeul_jong.insert(pair<string, int>("��", 27));
}


wchar_t combine_hangul(string ch, string ch2, string ch3)
{
    setlocale(LC_CTYPE, "");

    map<string, int> hangeul_cho;
    map<string, int> hangeul_jung;
    map<string, int> hangeul_jong;
    init_cho(hangeul_cho);
    init_jung(hangeul_jung);
    init_jong(hangeul_jong);

    wchar_t cho = hangeul_cho.at(ch);
    wchar_t j1 = hangeul_jung[ch2];
    wchar_t j2 = hangeul_jong[ch3];

    //wchar_t star = 0x2605;
    wchar_t abc = 44032 + cho * 21 * 28 + j1 * 28 + j2;

    //wchar_t test = 44912;
    wprintf(L"%lc", abc);
    return abc;
}

vector<string> moum_n{ "110001", // ���� ���� ���� Ȯ�ο�. ���� + ��������
                       "001110",
                       "011100",
                       "100011",
                       "101001",
                       "001101",
                       "101100",
                       "100101",
                       "010101",
                       "101010",
                       "111010",
                       "001110",
                       "101110",
                       "001100",
                       "111001",
                       "111001",
                       "111100",
                       "111100",
                       "101100",
                       "010111",
                       "100111",
                       "011111",
                       "011110",
                       "100001",
                       "110011",
                       "110111",
                       "101101",
                       "111011",
                       "111111",
                       "110110",
                       "111101",
                       "101011",
                       "011101",
                       "111110" };

vector<string> moum_b{ "110001", // ���� ���� Ȯ�ο�. ���� + �����ٶ� ����
                       "001110",
                       "011100",
                       "100011",
                       "101001",
                       "001101",
                       "101100",
                       "100101",
                       "010101",
                       "101010",
                       "111010",
                       "001110",
                       "101110",
                       "001100",
                       "111001",
                       "111001",
                       "111100",
                       "111100",
                       "101100",
                       "010111",
                       "110101",
                       "100100",
                       "010100",
                       "100010",
                       "000110",
                       "111000",
                       "000101",
                       "110100",
                       "110010",
                       "100110",
                       "010110" };

vector<string> doinsori{ "000100",
/*�ȼҸ� ����*/           "010100",
                         "000110",
                         "000001",
                         "000101" };

vector<string> excep{ "000111",
                      "001100",
                      "000001",
                      "001110",
                      "101100",
                      "111001",
                      "111100",
                      "100100",
                      "010100",
                      "100010",
                      "000110",
                      "000101",
                      "110100",
                      "110010",
                      "100110",
                      "010110" };

void brailleInit(map<string, vector<string>>& koreanBrailleMap)
{
    koreanBrailleMap["000100"].push_back("��");
    koreanBrailleMap["000001"].push_back("��"); //  000100
    koreanBrailleMap["100100"].push_back("��");
    koreanBrailleMap["010100"].push_back("��");
    koreanBrailleMap["000001"].push_back("��"); //  010100
    koreanBrailleMap["000010"].push_back("��");
    koreanBrailleMap["100010"].push_back("��");
    koreanBrailleMap["000110"].push_back("��");
    koreanBrailleMap["000001"].push_back("��"); //  000110
    koreanBrailleMap["000001"].push_back("��");
    koreanBrailleMap["000001"].push_back("��"); //  000001
    koreanBrailleMap["000000"].push_back(" ");
    koreanBrailleMap["000101"].push_back("��");
    koreanBrailleMap["000001"].push_back("��"); //  000101
    koreanBrailleMap["000011"].push_back("��");
    koreanBrailleMap["110100"].push_back("��");
    koreanBrailleMap["110010"].push_back("��");
    koreanBrailleMap["100110"].push_back("��");
    koreanBrailleMap["010110"].push_back("��");
    koreanBrailleMap["100000"].push_back("��,");
    koreanBrailleMap["010010"].push_back("��,");
    koreanBrailleMap["001010"].push_back("��,");
    koreanBrailleMap["010000"].push_back("��,");
    koreanBrailleMap["010001"].push_back("��,");
    koreanBrailleMap["110000"].push_back("��,");
    koreanBrailleMap["001000"].push_back("��,");
    koreanBrailleMap["011011"].push_back("��,");
    koreanBrailleMap["101000"].push_back("��,");
    koreanBrailleMap["011000"].push_back("��,");
    koreanBrailleMap["011010"].push_back("��,");
    koreanBrailleMap["011001"].push_back("��,");
    koreanBrailleMap["010011"].push_back("��,");
    koreanBrailleMap["001011"].push_back("��,");
    koreanBrailleMap["001100"].push_back("��,");
    koreanBrailleMap["110001"].push_back("��");
    koreanBrailleMap["001110"].push_back("��");
    koreanBrailleMap["011100"].push_back("��");
    koreanBrailleMap["100011"].push_back("��");
    koreanBrailleMap["101001"].push_back("��");
    koreanBrailleMap["001101"].push_back("��");
    koreanBrailleMap["101100"].push_back("��");
    koreanBrailleMap["100101"].push_back("��");
    koreanBrailleMap["010101"].push_back("��");
    koreanBrailleMap["101010"].push_back("��");
    koreanBrailleMap["111010"].push_back("��");
    koreanBrailleMap["001110"].push_back("��"); //  111010
    koreanBrailleMap["101110"].push_back("��");
    koreanBrailleMap["001100"].push_back("��");
    koreanBrailleMap["111001"].push_back("��");
    koreanBrailleMap["111001"].push_back("��"); //  111010
    koreanBrailleMap["101111"].push_back("��");
    koreanBrailleMap["111100"].push_back("��");
    koreanBrailleMap["111100"].push_back("��"); //  111010
    koreanBrailleMap["101100"].push_back("��"); //  111010
    koreanBrailleMap["010111"].push_back("��");
    koreanBrailleMap["110101"].push_back("����");
    koreanBrailleMap["100100"].push_back("����");
    koreanBrailleMap["010100"].push_back("����");
    koreanBrailleMap["100010"].push_back("����");
    koreanBrailleMap["000110"].push_back("����");
    koreanBrailleMap["111000"].push_back("����");
    koreanBrailleMap["000101"].push_back("����");
    koreanBrailleMap["110100"].push_back("����");
    koreanBrailleMap["110010"].push_back("����");
    koreanBrailleMap["100110"].push_back("����");
    koreanBrailleMap["010110"].push_back("����");
    koreanBrailleMap["100111"].push_back("�ä�,");
    koreanBrailleMap["011111"].push_back("�ä�,");
    koreanBrailleMap["011110"].push_back("�ä�,");
    koreanBrailleMap["100001"].push_back("�Ť�,");
    koreanBrailleMap["110011"].push_back("�Ť�,");
    koreanBrailleMap["110111"].push_back("�Ť�,");
    koreanBrailleMap["101101"].push_back("�Ǥ�,");
    koreanBrailleMap["111011"].push_back("�Ǥ�,");
    koreanBrailleMap["111111"].push_back("�Ǥ�,");
    koreanBrailleMap["110110"].push_back("�̤�,");
    koreanBrailleMap["111101"].push_back("�̤�,");
    koreanBrailleMap["101011"].push_back("�Ѥ�,");
    koreanBrailleMap["011101"].push_back("�Ѥ�,");
    koreanBrailleMap["111110"].push_back("�Ӥ�,");
    koreanBrailleMap["000111"].push_back("���ä�,"); //  011100
}

void brailleExceptionInit(map<string, vector<string>>& BrailleEx)
{
    BrailleEx["000001"].push_back("��");
    BrailleEx["000001"].push_back("��"); //  000100
    BrailleEx["000001"].push_back("��"); //  010100
    BrailleEx["000001"].push_back("��"); //  000110  
    BrailleEx["000001"].push_back("��"); //  000001
    BrailleEx["000001"].push_back("��"); //  000101

    BrailleEx["000111"].push_back("���ä�,"); //  011100

    BrailleEx["001100"].push_back("��,"); // ����
    BrailleEx["001100"].push_back("��");

    BrailleEx["100100"].push_back("��");
    BrailleEx["100100"].push_back("����");
    BrailleEx["010100"].push_back("��");
    BrailleEx["010100"].push_back("����");
    BrailleEx["100010"].push_back("��");
    BrailleEx["100010"].push_back("����");
    BrailleEx["000110"].push_back("��");
    BrailleEx["000110"].push_back("����");
    BrailleEx["000101"].push_back("��");
    BrailleEx["000101"].push_back("����");
    BrailleEx["110100"].push_back("��");
    BrailleEx["110100"].push_back("����");
    BrailleEx["110010"].push_back("��");
    BrailleEx["110010"].push_back("����");
    BrailleEx["100110"].push_back("��");
    BrailleEx["100110"].push_back("����");
    BrailleEx["010110"].push_back("��");
    BrailleEx["010110"].push_back("����");

    BrailleEx["001110"].push_back("��");
    BrailleEx["001110"].push_back("��"); //  111010
    BrailleEx["101100"].push_back("��");
    BrailleEx["101100"].push_back("��"); //  111010
    BrailleEx["111001"].push_back("��");
    BrailleEx["111001"].push_back("��"); //  111010
    BrailleEx["111100"].push_back("��");
    BrailleEx["111100"].push_back("��"); //  111010    
}

void div_exc_index(string letter, int& index)
{
    if (letter == excep[0]) //��
    {
        index = 1;
    }
    else if (letter == excep[1]) // ��,��
    {
        index = 2;
    }
    else if (letter == excep[2])    // ������������
    {
        index = 3;
    }
    else if (letter == excep[3] || letter == excep[4] || letter == excep[5] || letter == excep[6])    //���Ȥͤ�
    {
        index = 4;
    }
    else if (letter == excep[7] || letter == excep[8] || letter == excep[9] || letter == excep[10] || letter == excep[11] ||
        letter == excep[12] || letter == excep[13] || letter == excep[14] || letter == excep[15])   // ������������������
    {
        index = 5;
    }
    else
    {
    }
}


void check_moum_n(string letter, int& index)
{
    for (size_t i = 0; i < moum_n.size(); i++)
    {
        if (letter == moum_n[i])
        {
            index = 0;
            break;
        }
        else
        {
            index = 1;
        }
    }
}

void check_moum_b(string letter, int& index)
{
    for (size_t i = 0; i < moum_b.size(); i++)
    {
        if (letter == moum_b[i])
        {
            index = 0;
            break;
        }
        else
        {
            index = 1;
        }
    }
}

void check_doinsori(string letter, int& index, int& flag)
{
    flag = 0;
    if (letter == doinsori[0])
    {
        index = 1;
    }
    else if (letter == doinsori[1])
    {
        index = 2;
    }
    else if (letter == doinsori[2])
    {
        index = 3;
    }
    else if (letter == doinsori[3])
    {
        index = 4;
    }
    else if (letter == doinsori[4])
    {
        index = 5;
    }
    else
    {
        index = 0;
        flag = 1;
    }
}