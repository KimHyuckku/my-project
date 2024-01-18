#pragma once
#include "afxdialogex.h"


// CNameDlg2 대화 상자

class CNameDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CNameDlg2)

public:
	CNameDlg2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNameDlg2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ctrlCheck;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
