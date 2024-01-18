// DlgTest.cpp: 구현 파일
//

#include "pch.h"
#include "MExDlg.h"
#include "afxdialogex.h"
#include "DlgTest.h"


// CDlgTest 대화 상자

IMPLEMENT_DYNAMIC(CDlgTest, CDialog)

CDlgTest::CDlgTest(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIGTEST, pParent)
	, m_bCheckButton(FALSE)
	, m_strEdit(_T(""))
{

}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bCheckButton);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Control(pDX, IDC_SLIDER1, m_Sliderctrl);
	DDX_Control(pDX, IDC_SLIDER2, m_Sliderctrl2);
	DDX_Control(pDX, IDC_SLIDER3, m_Sliderctrl3);
	DDX_Control(pDX, IDC_PICTURE, m_Picturectrl);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgTest::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTest::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgTest::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgTest::OnBnClickedRadio2)



	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgTest::OnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgTest::OnSelchangeCombo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CDlgTest::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CDlgTest::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CDlgTest::OnNMCustomdrawSlider3)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgTest::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgTest::OnClickedButton4)
END_MESSAGE_MAP()


// CDlgTest 메시지 처리기


void CDlgTest::OnBnClickedCheck1()
{
	UpdateData(FALSE); // 바뀐 데이터 값을 가져옴
	CString message;
	message.Format(_T("Check button press value:%d"),m_bCheckButton);
	AfxMessageBox(message);

}


void CDlgTest::OnBnClickedButton1()
{
	int position1, position2, position3;
	CString message;

	position1 = m_Sliderctrl.GetPos();
	position2 = m_Sliderctrl2.GetPos();
	position3 = m_Sliderctrl3.GetPos();

	message.Format(_T("Your Birthday is %d year %d month %d day"), position1, position2, position3);

	AfxMessageBox(message);

}


void CDlgTest::OnBnClickedRadio1()
{
	AfxMessageBox(_T("Radio Button 1 Press"));	

}


void CDlgTest::OnBnClickedRadio2()
{
	AfxMessageBox(_T("Radio Button 2 Press"));

}



BOOL CDlgTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strEdit = _T("Welcome to Hell Everyone!!");
	UpdateData(FALSE);
	CString data;
	for (int i = 1; i < 11; i++)
	{
		data.Format(_T("List data%d"), i);
		m_ListBox.AddString(data);
		data.Format(_T("Combo data%d"), i);
		m_ComboBox.AddString(data);
	}
	m_Sliderctrl.SetRange(1900, 2023, TRUE);
	m_Sliderctrl.SetPos(2023);

	m_Sliderctrl2.SetRange(1, 12, TRUE);
	m_Sliderctrl2.SetPos(1);

	m_Sliderctrl3.SetRange(1, 31, TRUE);
	m_Sliderctrl3.SetPos(1);


	return TRUE;
}



void CDlgTest::OnSelchangeList1()
{
	int num = m_ListBox.GetCurSel();//Search the current position
	CString data;
	m_ListBox.GetText(num, data);//get character at select position
	AfxMessageBox(data);//output message box

}


void CDlgTest::OnSelchangeCombo1()
{
	int num = m_ComboBox.GetCurSel();
	CString data;
	m_ComboBox.GetLBText(num, data);
	AfxMessageBox(data);

}


void CDlgTest::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int position;
	position = m_Sliderctrl.GetPos();
	SetDlgItemInt(IDC_EDIT2, position);


	*pResult = 0;
}


void CDlgTest::OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int position;
	position = m_Sliderctrl2.GetPos();
	SetDlgItemInt(IDC_EDIT3, position);

	*pResult = 0;
}


void CDlgTest::OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int position;
	position = m_Sliderctrl3.GetPos();
	SetDlgItemInt(IDC_EDIT4, position);

	*pResult = 0;
}



void CDlgTest::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgTest::OnClickedButton4()
{
	CRect rect;		//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_Picturectrl.GetWindowRect(rect);	//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_Picturectrl.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("1.jpg"));//이미지 로드

	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);//DC 해제
}
