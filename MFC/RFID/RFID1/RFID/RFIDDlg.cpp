// RFIDDlg.cpp: 구현 파일
//
#include "is_d2xx.h"
#include "pch.h"
#include "framework.h"
#include "RFID.h"
#include "RFIDDlg.h"
#include "afxdialogex.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <atlstr.h>
using namespace std;

// sound 출력용
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include "mmsystem.h"

#pragma comment(lib,"winmm.lib") // 라이브러리 불러오기

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_DATA 100

string st_string[10];

string st_data_number;
string st_card_number;
CString cs_st_card_number;
string st_name;
string st_number;
string st_picture;
string st_borrow_flag;
string st_borrow_date;
string st_return_date;
string st_book_number;
int st_flag;

string bo_data_number;
string bo_card_number;
CString cs_bo_card_number;
string bo_name;
string bo_number;
string bo_picture;

string book_number;

void find_student(CString _m_strRfid);
void find_book(CString _m_strRfid);


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRFIDDlg 대화 상자



CRFIDDlg::CRFIDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RFID_DIALOG, pParent)
	, m_strRfid(_T(""))
	, m_strRfid2(_T(""))
	, st_strRfid(_T(""))
	, st_strRfid2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}
CRFIDDlg::~CRFIDDlg()
{
	OnDisconnect();
}

void CRFIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Text(pDX, IDC_EDIT2, m_strRfid); // st_name[st_flag]);
	DDX_Text(pDX, IDC_EDIT1, st_name);
	DDX_Text(pDX, IDC_EDIT3, st_number);
	DDX_Text(pDX, IDC_EDIT4, st_borrow_date);
	DDX_Text(pDX, IDC_EDIT5, st_book_number);

	DDX_Text(pDX, IDC_EDIT7, m_strRfid2);
	DDX_Text(pDX, IDC_EDIT6, bo_name);
	DDX_Text(pDX, IDC_EDIT8, bo_number);
}

BEGIN_MESSAGE_MAP(CRFIDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRFIDDlg::OnConnect)
	ON_BN_CLICKED(IDC_BUTTON3, &CRFIDDlg::OnReadOnce)
	ON_BN_CLICKED(IDC_BUTTON2, &CRFIDDlg::OnDisconnect)
	ON_BN_CLICKED(IDC_BUTTON4, &CRFIDDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CRFIDDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CRFIDDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CRFIDDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDOK, &CRFIDDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRFIDDlg 메시지 처리기

BOOL CRFIDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	//SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRFIDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRFIDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRFIDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRFIDDlg::OnConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//열린 포트번호 찾기
	if (is_GetDeviceNumber(&usbnumber) == IS_OK)
	{
		printf("FTDI USB To Serial 연결된 개수 : %d\n", usbnumber);
		if (is_GetSerialNumber(0, readSerialNumber) == IS_OK)
		{
			if (memcmp(changeSerialNumber, readSerialNumber, sizeof(changeSerialNumber) != 0))
			{
				if (is_SetSerialNumber(0, changeSerialNumber) == IS_OK)
				{
					printf(" USB To Serial Number 를 변경 하였습니다.\n");
					printf(" FTDI SerialNumber :  %s \n", changeSerialNumber);
				}
			}
			else
				printf(" FTDI SerialNumber :  %s \n", changeSerialNumber);
		}
	}

	//열린 포트번호로 연결
	unsigned long portNumber;
	if (is_GetCOMPort_NoConnect(0, &portNumber) == IS_OK)
	{
		printf("COM Port : %d\n", portNumber);
	}
	if (is_OpenSerialNumber(&ftHandle, readSerialNumber, 115200) != IS_OK)
	{
		printf("USB To Serial과 통신 연결 실패\n");
		//return -1;
	}
	else {
		printf("Serial포트 %d와 통신 연결성공!! \n", portNumber);
	}
	Sleep(100);
	flag_r = 0;

}


void CRFIDDlg::OnReadOnce()
{
	CString temp, temp1 = _T("");
	CString temp2, temp3 = _T("");
	CString st_temp, st_temp1 = _T("");
	CString st_temp2, st_temp3 = _T("");
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//ISO15693모드로 읽기( 싱글모드 읽기 )
	if (flag_r == 0)
	{
		if (is_WriteReadCommand(ftHandle, CM1_ISO15693, CM2_ISO15693_ACTIVE + BUZZER_ON,
			writeLength, wirteData, &readLength, readData) == IS_OK)
		{
			int i;
			printf("ISO 15693 UID : ");
			for (i = 0; i < readLength; i++)
			{
				temp.Format(_T("%02x "), readData[i]);
				st_temp.Format(_T("%02x"), readData[i]);

				temp1 += temp;
				st_temp1 += st_temp;
				printf("%02x ", readData[i]);
			}
			m_strRfid2 = temp1;
			st_strRfid2 = st_temp1;

			find_book(st_strRfid2);
			UpdateData(FALSE);
			printf("\n");
		}
	}
	else
	{
		// read continue mode
	}

	//ISO14443A모드로 읽기
	if (is_WriteReadCommand(ftHandle, CM1_ISO14443AB, CM2_ISO14443A_ACTIVE + BUZZER_ON,
		writeLength, wirteData, &readLength, readData) == IS_OK)
	{
		int i;
		printf("ISO 14443AB UID : ");
		for (i = 0; i < readLength; i++)
		{
			temp2.Format(_T("%02x "), readData[i]);
			st_temp2.Format(_T("%02x"), readData[i]);

			temp3 += temp2;
			st_temp3 += st_temp2;
			printf("%02x ", readData[i]);
		}
		m_strRfid = temp3;
		st_strRfid = st_temp3;

		find_student(st_strRfid);
		UpdateData(FALSE);
		printf("\n");
	}
		
}




void CRFIDDlg::OnDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// 무선파워를 끊어요.
	is_RfOff(ftHandle);
	//USB 포트를 Close
	if (is_Close(ftHandle) == IS_OK)
	{
		st_data_number.Empty();
		st_card_number.Empty();
		st_name.Empty();
		st_number.Empty();
		st_picture.Empty();
		st_borrow_flag.Empty();
		st_borrow_date.Empty();
		st_return_date.Empty();
		st_book_number.Empty();
		st_flag = 0;

		bo_data_number.Empty();
		bo_card_number.Empty();
		bo_name.Empty();
		bo_number.Empty();
		bo_picture.Empty();
		m_strRfid.Empty();
		m_strRfid2.Empty();

		book_number="";

		printf("연결을 닫습니다. \n");
	}

}

void CRFIDDlg::OnBnClickedButton4()
{
	/////////////////////////////////  이미지 출력  /////////////////////////////////
	CRect m_rect;
	CBitmap m_bitmap;
	//CString Path_img = "img\\null.bmp";
	CString Path_img = st_picture; //_T("img\\beer.bmp");
	m_bitmap.DeleteObject();
	m_bitmap.Attach((HBITMAP)LoadImage(NULL, Path_img, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	CDC* pDC = GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(m_bitmap);
	((CStatic*)GetDlgItem(IDC_STATIC02))->GetWindowRect(m_rect);
	ScreenToClient(&m_rect);
	CClientDC   dc(this);

	dc.BitBlt(60, 25, 320, 200, &memDC, 0, 0, SRCCOPY);

	ReleaseDC(pDC);
	DeleteDC(memDC);
}

void CRFIDDlg::OnBnClickedButton5()
{
	CRect m_rect;
	CBitmap m_bitmap;
	//CString Path_img = "img\\null.bmp";
	CString Path_img = bo_picture; //_T("img\\beer.bmp");
	m_bitmap.DeleteObject();
	m_bitmap.Attach((HBITMAP)LoadImage(NULL, Path_img, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	CDC* pDC = GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(m_bitmap);
	((CStatic*)GetDlgItem(IDC_STATIC03))->GetWindowRect(m_rect);
	ScreenToClient(&m_rect);
	CClientDC   dc(this);

	dc.BitBlt(680, 25, 280, 200, &memDC, 0, 0, SRCCOPY);

	ReleaseDC(pDC);
	DeleteDC(memDC);
}


void CRFIDDlg::OnBnClickedButton6()
{
	if (book_number == "")
	{
		AfxMessageBox(_T("책 카드를 찍어주세요."));
	}
	else if (st_number == "")
	{
		AfxMessageBox(_T("학생 카드를 찍어주세요."));
	}
	else
	{
		if (st_borrow_flag == _T("0"))
		{
			ofstream fiout("c:\\work\\MFC\\RFID\\RFID\\RFID\\data\\student_data.csv");
			if (!fiout) { // 열기 실패 검사
				cout << "student_data 파일을 열 수 없다\n";
			}

			for (int i = 0; i < st_flag; i++)
			{
				fiout << st_string[i] << "\n";
			}
			fiout << string(CT2CA(st_data_number)) << "," << string(CT2CA(st_card_number)) << "," << string(CT2CA(st_name))
				  << "," << string(CT2CA(st_number)) << "," << string(CT2CA(st_picture)) << ",1," << "여긴수정중"
				  << "," << "여기도수정해야됨" << "," << book_number << endl;
			for (int i = st_flag+1; i < 5; i++)
			{
				fiout << st_string[i] << "\n";
			}


			//fiout << name << "," << school_number << "," << name << ",안녕하세요, 이거 띄어쓰기도 되냐?, ㅏㅁㄴ\n"; // name 쓰기
			//fiout << school_number << "," << dept << "\n"; // sid 쓰기
			//fiout << dept << "\n"; // dept 쓰기

			fiout.close(); // 파일 닫기	
			AfxMessageBox(_T("대출이 완료되었습니다."));
		}
		else
		{
			AfxMessageBox(_T("빌린 책이 존재합니다!!\n 반납한 뒤 빌려주세요."));
		}



	}
}

void CRFIDDlg::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CRFIDDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void find_student(CString _m_strRfid)
{
	int i;
	char temp[100], temp0[100], * context=NULL;
	string temp2;


	ifstream fin;
	fin.open("c:\\work\\MFC\\RFID\\RFID\\RFID\\data\\student_data.csv");
	if (!fin) {  // 파일 열기 실패 확인
		cout << "student_data 파일을 열 수 없다\n";
	}
		
	fin >> temp;	// 맨 윗줄 없얘는 용도
	st_string[0] = temp;

	for (i = 1; i < 5; i++)
	{
		fin >> temp0;
		st_string[i] = temp0;

		temp2 = strtok_s(temp0, ",", &context);
		st_data_number=temp2.c_str();

		temp2 = strtok_s(NULL, ",", &context);
		st_card_number = temp2.c_str();				//wcout << (const wchar_t*)st_name << endl; 잘 나오는지 확인용 코드

		temp2 = strtok_s(NULL, ",", &context);
		st_name = temp2.c_str();

		temp2 = strtok_s(NULL, ",", &context);
		st_number = temp2.c_str();
		
		temp2 = strtok_s(NULL, ",", &context);
		st_picture = temp2.c_str();

		temp2 = strtok_s(NULL, ",", &context);
		st_borrow_flag = temp2.c_str();

		if (st_borrow_flag == _T("0"))
		{
			st_borrow_date.Format(_T("빌린 책 없음"));
			st_return_date.Format(_T("0"));
			st_book_number.Format(_T("0"));
		}
		else
		{
			temp2 = strtok_s(NULL, ",", &context);
			st_borrow_date = temp2.c_str();

			temp2 = strtok_s(NULL, ",", &context);
			st_return_date = temp2.c_str();

			temp2 = strtok_s(NULL, ",", &context);
			st_book_number = temp2.c_str();
		}

		if (cs_st_card_number == _m_strRfid)
		{
			st_flag = i;

			for (int j = i + 1; j < 5; j++)
			{
				fin >> temp0;
				st_string[j] = temp0;
			}
			break;
		}
	}

	fin.close();
}


void find_book(CString _m_strRfid)
{
	int i;
	char temp[100], temp0[100], * context = NULL;
	string temp2;


	ifstream bk_fin;
	bk_fin.open("c:\\work\\RFID\\RFID\\RFID\\data\\book_data.csv");
	if (!bk_fin) {  // 파일 열기 실패 확인
		cout << "book_data파일을 열 수 없다";
	}

	bk_fin >> temp;	// 맨 윗줄 없얘는 용도

	for (i = 1; i < 3; i++)
	{
		bk_fin >> temp0;
		cout << temp0 << endl;

		temp2 = strtok_s(temp0, ",", &context);
		bo_data_number = temp2.c_str();

		temp2 = strtok_s(NULL, ",", &context);
		bo_card_number = temp2.c_str();				//wcout << (const wchar_t*)st_name << endl; 잘 나오는지 확인용 코드

		temp2 = strtok_s(NULL, ",", &context);
		bo_name = temp2.c_str();

		temp2 = strtok_s(NULL, ",", &context);
		bo_number = temp2.c_str();
		book_number = temp2;

		temp2 = strtok_s(NULL, ",", &context);
		bo_picture = temp2.c_str();


		if (cs_bo_card_number == _m_strRfid) break;

	}
	bk_fin.close();
}

