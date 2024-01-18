
// MExListCtrlDlgDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MExListCtrlDlg.h"
#include "MExListCtrlDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMExListCtrlDlgDlg 대화 상자



CMExListCtrlDlgDlg::CMExListCtrlDlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEXLISTCTRLDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}




void CMExListCtrlDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	//enum { IDD = IDD_MEXLISTCTRL_DIALOG };
	//CListCtrl m_ListCtrl;

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CMExListCtrlDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMExListCtrlDlgDlg::OnSelchangeCombo1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMExListCtrlDlgDlg::OnItemchangedList1)
END_MESSAGE_MAP()


// CMExListCtrlDlgDlg 메시지 처리기

BOOL CMExListCtrlDlgDlg::OnInitDialog()
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
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// Prepare to memory allocation
	m_largeImage = new CImageList;
	m_smallImage = new CImageList;

	m_largeImage->Create(32, 32, ILC_COLOR4, 3, 3);
	m_smallImage->Create(16, 16, ILC_COLOR4, 3, 3);

	// add a picture for Image list
	CBitmap cBit;
	cBit.LoadBitmap(IDB_BITMAP1);
	m_largeImage->Add(&cBit, RGB(255, 255, 255));
	cBit.DeleteObject();
	cBit.LoadBitmap(IDB_BITMAP2);
	m_largeImage->Add(&cBit, RGB(255, 255, 255));
	cBit.DeleteObject();
	cBit.LoadBitmap(IDB_BITMAP3);
	m_largeImage->Add(&cBit, RGB(255, 255, 255));

	cBit.DeleteObject();
	cBit.LoadBitmap(IDB_BITMAP4);
	m_smallImage->Add(&cBit, RGB(255, 255, 255));
	cBit.DeleteObject();
	cBit.LoadBitmap(IDB_BITMAP5);
	m_smallImage->Add(&cBit, RGB(255, 255, 255));
	cBit.DeleteObject();
	cBit.LoadBitmap(IDB_BITMAP6);
	m_smallImage->Add(&cBit, RGB(255, 255, 255));
	cBit.DeleteObject();

	m_ListCtrl.SetImageList(m_largeImage, LVSIL_NORMAL);
	m_ListCtrl.SetImageList(m_smallImage, LVSIL_SMALL);

	//Make a column
	LV_COLUMN lvcolumn;
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_LEFT;
	lvcolumn.iSubItem = 0;
	lvcolumn.cx = 80;
	lvcolumn.pszText = _T("Robert");
	m_ListCtrl.InsertColumn(0, &lvcolumn);

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_LEFT;
	lvcolumn.iSubItem = 1;
	lvcolumn.cx = 280;
	lvcolumn.pszText = _T("Comments");
	m_ListCtrl.InsertColumn(1, &lvcolumn);

	LV_ITEM lvitem;
	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvitem.iItem = 0;
	lvitem.iSubItem = 0;
	lvitem.pszText = _T("PUMA");
	lvitem.iImage = 0;
	m_ListCtrl.InsertItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = 0;
	lvitem.iSubItem = 1;
	lvitem.pszText = _T("Working a Industrial");
	m_ListCtrl.SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvitem.iSubItem = 0;
	lvitem.iItem = 1;
	lvitem.pszText = _T("Mobile Robot");
	lvitem.iImage = 1;
	m_ListCtrl.InsertItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = 1;
	lvitem.iSubItem = 1;
	lvitem.pszText = _T("Cleannig the room");
	m_ListCtrl.SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvitem.iItem = 2;
	lvitem.iSubItem = 0;
	lvitem.pszText = _T("Soccer Robot");
	lvitem.iImage = 2;
	m_ListCtrl.InsertItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = 2;
	lvitem.iSubItem = 1;
	lvitem.pszText = _T("playing a soccer");
	m_ListCtrl.SetItem(&lvitem);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMExListCtrlDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMExListCtrlDlgDlg::OnPaint()
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
HCURSOR CMExListCtrlDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMExListCtrlDlgDlg::OnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CComboBox* pcombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int num = pcombo->GetCurSel();
	DWORD style = ::GetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE);
	style &= ~(LVS_TYPEMASK);
	switch (num)
	{
	case 0:		style |= LVS_REPORT;
		break;
	case 1:		style |= LVS_ICON;
		break;
	case 2:		style |= LVS_SMALLICON;
		break;
	default:		style |= LVS_LIST;
		break;
	}
	::SetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE, (LONG)style);
}


void CMExListCtrlDlgDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString message;
	int num = pNMLV->iItem;
	static int oldnum = 0;

	if (num > -1 && oldnum != num)
	{
		message = m_ListCtrl.GetItemText(num, 0);
		AfxMessageBox(message);
		oldnum = num;
	}

	*pResult = 0;
}
