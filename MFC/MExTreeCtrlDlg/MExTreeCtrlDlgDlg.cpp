
// MExTreeCtrlDlgDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MExTreeCtrlDlg.h"
#include "MExTreeCtrlDlgDlg.h"
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


// CMExTreeCtrlDlgDlg 대화 상자



CMExTreeCtrlDlgDlg::CMExTreeCtrlDlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEXTREECTRLDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMExTreeCtrlDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
}

BEGIN_MESSAGE_MAP(CMExTreeCtrlDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMExTreeCtrlDlgDlg::OnSelchangedTreeOn)
END_MESSAGE_MAP()


// CMExTreeCtrlDlgDlg 메시지 처리기

BOOL CMExTreeCtrlDlgDlg::OnInitDialog()
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

	//Image list setup
	pimagelist = new CImageList;
	pimagelist->Create(32, 32, ILC_COLOR4, 3, 3);
	pimagelist->Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	pimagelist->Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	pimagelist->Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	pimagelist->Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	pimagelist->Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	pimagelist->Add(AfxGetApp()->LoadIcon(IDI_ICON6));

	//tree setting
	m_TreeCtrl.SetImageList(pimagelist, TVSIL_NORMAL);

	TV_INSERTSTRUCT tvstruct;
	HTREEITEM item;

	// insert root data
	tvstruct.hParent = 0;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.pszText = _T("Animals");
	tvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 3;
	item = m_TreeCtrl.InsertItem(&tvstruct);

	// insert child data
	tvstruct.hParent = item;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.pszText = _T("Dog");
	tvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 3;
	m_TreeCtrl.InsertItem(&tvstruct);

	tvstruct.hParent = item;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.pszText = _T("Lion");
	tvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 3;
	m_TreeCtrl.InsertItem(&tvstruct);

	tvstruct.hParent = item;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.pszText = _T("Tiger");
	tvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 3;
	m_TreeCtrl.InsertItem(&tvstruct);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMExTreeCtrlDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMExTreeCtrlDlgDlg::OnPaint()
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
HCURSOR CMExTreeCtrlDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMExTreeCtrlDlgDlg::OnSelchangedTreeOn(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UINT flags;
	CPoint point;
	CString message;
	//Get mouse position
	GetCursorPos(&point);
	//position mapping the client region 
	m_TreeCtrl.ScreenToClient(&point);
	//get item using HitTest function
	HTREEITEM nitem = m_TreeCtrl.HitTest(point, &flags);
	//get string item’s string
	message = m_TreeCtrl.GetItemText(nitem);
	if (message.GetLength() > 0)
		AfxMessageBox(message);

	*pResult = 0;
}
