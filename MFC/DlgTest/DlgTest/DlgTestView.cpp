
// DlgTestView.cpp: CDlgTestView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DlgTest.h"
#endif

#include "DlgTestDoc.h"
#include "DlgTestView.h"
#include "NameDlg.h"
#include "NameDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgTestView

IMPLEMENT_DYNCREATE(CDlgTestView, CView)

BEGIN_MESSAGE_MAP(CDlgTestView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(IDD_DIALOG, &CDlgTestView::OnIddDialog)

ON_COMMAND(IDD_DIALOG, &CDlgTestView::OnIddDialog)
ON_COMMAND(IDD_CONTROL, &CDlgTestView::OnIddControl)
END_MESSAGE_MAP()

// CDlgTestView 생성/소멸

CDlgTestView::CDlgTestView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDlgTestView::~CDlgTestView()
{
}

BOOL CDlgTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDlgTestView 그리기

void CDlgTestView::OnDraw(CDC* /*pDC*/)
{
	CDlgTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CDlgTestView 인쇄

BOOL CDlgTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDlgTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDlgTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDlgTestView 진단

#ifdef _DEBUG
void CDlgTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDlgTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDlgTestDoc* CDlgTestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDlgTestDoc)));
	return (CDlgTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CDlgTestView 메시지 처리기

void CDlgTestView::OnIddDialog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CNameDlg dlg;
	dlg.m_strName = _T("ㅇㅅㅇ");
	dlg.m_nAge = 19;

	if (dlg.DoModal() == IDOK)
	{
		CString strOutText, strOutText2, temp;
		strOutText.Format(_T("Name: %s, Age: %d\n License %d "),
			dlg.m_strName, dlg.m_nAge, dlg.m_bLicense);
//		AfxMessageBox(strOutText);

		strOutText2.Format(_T("Job: %d, Residence: %d\n License %d "),
			dlg.m_nJob, dlg.m_nResidence, dlg.m_bLicense);
//		AfxMessageBox(strOutText2);

		temp = strOutText + strOutText2;
		AfxMessageBox(temp);
	}

}

void CDlgTestView::OnIddControl()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CNameDlg2 dlg2;

	CString temp;

	if (dlg2.DoModal() == IDOK)
	{
		temp.Format(_T("Control 키가 눌렸음!\n"));
		AfxMessageBox(temp);
	}
	else
	{
	//	CDlgTestView::OnIddDialog();
	}
}