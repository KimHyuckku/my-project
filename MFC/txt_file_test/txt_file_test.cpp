#if 0
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {


    string str_buf;
    fstream fs;

    fs.open("test.csv", ios::in);

    while (!fs.eof()) {
        getline(fs, str_buf, ',');
        cout << str_buf << endl;
    }
    fs.close();

    return 0;
}

#endif


#if 0
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	// 스트림 객체 생성 및 파일 열기
	ifstream fin;
	fin.open("c:\\work\\sungjuk.csv");
	if (!fin) {  // 파일 열기 실패 확인
		cout << "파일을 열 수 없다";
		return 0;
	}

	char name[100], dept[200], * context = NULL;;
	char sid[100];

    string st[10];

    char st1[100];
    char st2[100];
    char st3[100];


	// 파일 읽기
	fin >> name; // 파일에 있는 문자열을 읽어서 name 배열에 저장
	fin >> sid; // 정수를 읽어서 sid 정수형 변수에 저장
	fin >> dept; // 문자열을 읽고 dept 배열에 저장


    st1 = strtok_s(name, ",", &context);

    st2 = strtok_s(NULL, ",", &context);

    st3 = strtok_s(NULL, ",", &context);

	// 읽은 텍스트를 화면에 출력
    cout << name << endl;
    cout << st1 << st2 << st3 << endl;
	cout << sid << endl;
	cout << dept << endl;

	fin.close(); // 파일 읽기를 마치고 파일을 닫는다.
}



#endif

#if 0
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    char name[10], dept[20];
    int school_number;

    cout << "이름 : ";
    cin >> name;
    cout << "학번 : ";
    cin >> school_number;
    cout << "학과 : ";
    cin >> dept;


    ofstream fiout("c:\\work\\student.csv");
    if (!fiout) { // 열기 실패 검사
        cout << "c:\\work\\student.txt 파일을 열 수 없다";
            return 0;
    }

    fiout << name << "," << school_number << "\n"; // name 쓰기
    fiout << school_number << "," << dept << "\n"; // sid 쓰기
    fiout << dept << "\n"; // dept 쓰기

    fiout.close(); // 파일 닫기

}
#endif

#if 1
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    string name, dept;
    int school_number;

    cout << "이름 : ";
    cin >> name;
    cout << "학번 : ";
    cin >> school_number;
    cout << "학과 : ";
    cin >> dept;


    ofstream fiout("c:\\work\\student.csv");
    if (!fiout) { // 열기 실패 검사
        cout << "c:\\work\\student.txt 파일을 열 수 없다";
        return 0;
    }

    //fiout << name << "," << school_number << "," << name << ",안녕하세요, 이거 띄어쓰기도 되냐?, ㅏㅁㄴ\n"; // name 쓰기
    fiout << ",,\n";
    fiout << school_number << "," << dept << "\n"; // sid 쓰기
    fiout << dept << "\n"; // dept 쓰기

    fiout.close(); // 파일 닫기

}
#endif