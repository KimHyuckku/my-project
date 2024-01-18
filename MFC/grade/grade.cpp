#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
	// 스트림 객체 생성 및 파일 열기
	ifstream fin;
	fin.open("c:\\work\\sungjuk.csv"); // c:\\work\RFID\\img
	if (!fin) {  // 파일 열기 실패 확인
		cout << "파일을 열 수 없다";
		return 0;
	}

	//string sososo[10];

	char name[5], *context = 0;
	//char sid[100];
	//char dept[100];

	char name2[10], dept2[20];
	int school_number;

	//char collar[100];
	/*char* inum[100];
	char* iname[100];
	char* ikor[100];
	char* ieng[100];
	char* imath[100];*/

	//for (int i = 0; i < 10; i++)
	//{
	//	fin >> collar[i][100];
	//}
	


	//inum[1] = strtok_s(collar[1][100], ",", &context);   // ,기준으로  끊어서 구분
	//iname[1] = strtok_s(NULL, ",", &context);
	//ikor[1] = strtok_s(NULL, ",", &context);
	//ieng[1] = strtok_s(NULL, ",", &context);
	//imath[1] = strtok_s(NULL, ",", &context);

	//cout << inum[1] << " " << iname[1] << " " << ikor[1] << " " << ieng[1] << " " << imath[1] << endl;



	 //파일 읽기

	//for (int i = 0; i < 15; i++)
	//{
	//	fin >> name;
	//	
	//	context = 0;
	//	inum[i] = strtok_s(name, ",", &context);   // ,기준으로  끊어서 구분
	//	iname[i] = strtok_s(NULL, ",", &context);
	//	ikor[i] = strtok_s(NULL, ",", &context);
	//	ieng[i] = strtok_s(NULL, ",", &context);
	//	imath[i] = strtok_s(NULL, ",", &context);

	//	cout << inum[i] << " " << iname[i] << " " << ikor[i] << " " << ieng[i] << " " << imath[i] << endl;
	//}

	//fin >> name; // 파일에 있는 문자열을 읽어서 name 배열에 저장
	//fin >> sid; // 정수를 읽어서 sid 정수형 변수에 저장
	//fin >> dept; // 문자열을 읽고 dept 배열에 저장


	//sososo[0] = strtok_s(name, ",", &context);   // ,기준으로  끊어서 구분
	//sososo[1] = strtok_s(NULL, ",", &context);
	//sososo[2] = strtok_s(NULL, ",", &context);
	//sososo[3] = strtok_s(NULL, ",", &context);
	//sososo[4] = strtok_s(NULL, ",", &context);
	//

	//// 읽은 텍스트를 화면에 출력
	//cout << sososo[0] << " " << sososo[1] << " " << sososo[2] << " " << sososo[3] << " " << sososo[4] << endl;
	//cout << sid << endl;
	//cout << dept << endl;

	fin.close(); // 파일 읽기를 마치고 파일을 닫는다.

	cout << "이름 : ";
	cin >> name2;
	cout << "학번 : ";
	cin >> school_number;
	cout << "학과 : ";
	cin >> dept2;

	ofstream fiout("c:\\work\\student.csv");
	if (!fiout) { // 열기 실패 검사
		cout << "c:\\work\\student.txt 파일을 열 수 없다";
		return 0;
	}

	fiout << name2 << "," << school_number << "\n"; // name 쓰기
	fiout << school_number << "," << dept2 << "\n"; // sid 쓰기
	fiout << dept2 << "\n"; // dept 쓰기

	fiout.close(); // 파일 닫기

}
