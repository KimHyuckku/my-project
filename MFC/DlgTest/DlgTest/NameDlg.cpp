// NameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DlgTest.h"
#include "afxdialogex.h"
#include "NameDlg.h"


// CNameDlg 대화 상자

IMPLEMENT_DYNAMIC(CNameDlg, CDialogEx)

CNameDlg::CNameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strName(_T(""))
	, m_nAge(0)
	, m_bLicense(FALSE)
	, m_nJob(0)
	, m_nResidence(0)
{

}

CNameDlg::~CNameDlg()
{
}

void CNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strName);
	DDV_MaxChars(pDX, m_strName, 10); //최대 입력 값 제한
	DDX_Text(pDX, IDC_EDIT1, m_nAge);
	DDV_MinMaxInt(pDX, m_nAge, 0, 100); //최대 입력 값 제한
	DDX_Check(pDX, IDC_CHECK1, m_bLicense);
	DDX_Radio(pDX, IDC_RADIO2, m_nJob);
	DDX_Radio(pDX, IDC_RADIO6, m_nResidence);
}


BEGIN_MESSAGE_MAP(CNameDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &CNameDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &CNameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNameDlg 메시지 처리기


void CNameDlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNameDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
