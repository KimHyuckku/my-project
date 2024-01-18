
// MExTreeCtrlDlgDlg.h: 헤더 파일
//

#pragma once


// CMExTreeCtrlDlgDlg 대화 상자
class CMExTreeCtrlDlgDlg : public CDialogEx
{
// 생성입니다.
public:
	CImageList* pimagelist;
	CMExTreeCtrlDlgDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEXTREECTRLDLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_TreeCtrl;
	afx_msg void OnSelchangedTreeOn(NMHDR* pNMHDR, LRESULT* pResult);
};
