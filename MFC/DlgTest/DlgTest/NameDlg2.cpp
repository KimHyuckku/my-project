// NameDlg2.cpp: 구현 파일
//

#include "pch.h"
#include "DlgTest.h"
#include "afxdialogex.h"
#include "NameDlg2.h"


// CNameDlg2 대화 상자

IMPLEMENT_DYNAMIC(CNameDlg2, CDialog)

CNameDlg2::CNameDlg2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

CNameDlg2::~CNameDlg2()
{
}

void CNameDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlCheck);
}


BEGIN_MESSAGE_MAP(CNameDlg2, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CNameDlg2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNameDlg2::OnBnClickedButton2)
END_MESSAGE_MAP()


// CNameDlg2 메시지 처리기


void CNameDlg2::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ctrlCheck.ShowWindow(SW_SHOW);
}


void CNameDlg2::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ctrlCheck.ShowWindow(SW_HIDE);
}
