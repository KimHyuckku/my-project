#pragma once
#include "afxdialogex.h"


// CNameDlg 대화 상자

class CNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNameDlg)

public:
	CNameDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNameDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	int m_nAge;
	afx_msg void OnBnClickedCheck1();
	BOOL m_bLicence;
	afx_msg void OnBnClickedRadio5();
	int m_nJob;
	int m_nResidence;
	CButton m_ctrlCheck;
	
};
