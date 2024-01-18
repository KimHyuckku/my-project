
// MExListCtrlDlgDlg.h: 헤더 파일
//

#pragma once


// CMExListCtrlDlgDlg 대화 상자
class CMExListCtrlDlgDlg : public CDialogEx
{
// 생성입니다.
public:
	CMExListCtrlDlgDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CImageList* m_largeImage; //for Big Icon
	CImageList* m_smallImage; //for small Icon


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEXLISTCTRLDLG_DIALOG };

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
	CListCtrl m_ListCtrl;
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
};
