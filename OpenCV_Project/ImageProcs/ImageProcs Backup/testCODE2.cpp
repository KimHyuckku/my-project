#include "Braille_Def.h"

void print_Kor( string stringKor)//Korean - 3Bytes
{
    //SetConsoleOutputCP(949); //Terminal Consol Kor지원
    //SetConsoleOutputCP(65001); // 한글깨짐 해결
    const int KorOffset = 2;
    for (size_t i = 0; i < stringKor.size(); i += KorOffset)
    {
        std::cout << stringKor.substr(i, KorOffset);
    }
    std::cout << std::endl;
}

int main() {

    map<string, vector<string>> koreanBrailleMap;
    brailleInit(koreanBrailleMap);
    
   

    string abc = "100100"; // 나
    string sentence;


    int count = koreanBrailleMap[abc].size();
    cout << "바이너리 해당하는 문자 개수: " << count << endl;

    if (count > 1)
    {
        map<string, vector<string>> BrailleEx;
        brailleExceptionInit(BrailleEx);

        if (BrailleEx[abc].size() == 1)
        {
            sentence = *(BrailleEx[abc].data());
        }
        else if (BrailleEx[abc].size() == 2)
        {

        }
        else if (BrailleEx[abc].size() == BrailleEx["000001"].size())
        {

        }
        else if (BrailleEx[abc].size() == 8)
        {

        }
        else if (BrailleEx[abc].size() == 18)
        {

        }
        else
        {

        }



    }


    sentence += *(koreanBrailleMap[abc].data());
    sentence += *(koreanBrailleMap[abc].data() + 1);
    sentence += *(koreanBrailleMap["000000"].data());
    //sentence += *(koreanBrailleMap[abc].data()+2);
    cout << sentence << endl;



    for (size_t i = 0; i < count; i++)
    {
        std::cout << *(koreanBrailleMap[abc].data() + i) << ' ';
    }




    //string koraa = "앙앙앙";
    //std::cout << koraa <<std::endl;
    //print_Kor(koraa);
    //std::cout << " Map:\n";
    //for (const auto& pair : koreanBrailleMap) {
    //    std::cout << pair.first << " : ";
    //    for (size_t i = 0; i < pair.second.size(); ++i) {
    //        print_Kor(pair.second[i]);
    //    }
    //}

    // Map 데이터 출력
    std::cout << " Map:\n";
    for (const auto& pair : koreanBrailleMap) {
        std::cout << pair.first << " : ";
        
        for (const auto& value : pair.second) {
            //if (pair.first == "001100")
            std::cout << value << " ";
        }
       std::cout << "\n";
    }
    
    return 0;
}



void dev_exception(string letter, string letter_n)
{
    int sel;

    if (letter == "000001")
    {
        
    }
    else if (letter == "000111")
    {

    }
    else if (letter == "001100")
    {

    }

    /*switch(sel)
    {
    case 1:
        make_account();
        break;
    case 2:
        deposit_money();
        break;
    case 3:
        with_draw_money();
        break;
    case 4:
        show_all_acc_info();
        break;
    case 5:

        break;
    default:
        break;
    }*/
}