
// MExDlgView.cpp: CMExDlgView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MExDlg.h"
#endif

#include "MExDlgDoc.h"
#include "MExDlgView.h"
#include "DlgTest.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMExDlgView

IMPLEMENT_DYNCREATE(CMExDlgView, CView)

BEGIN_MESSAGE_MAP(CMExDlgView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDD_DIALOGSHOW, &CMExDlgView::OnDialogshow)
END_MESSAGE_MAP()

// CMExDlgView 생성/소멸

CMExDlgView::CMExDlgView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMExDlgView::~CMExDlgView()
{
}

BOOL CMExDlgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMExDlgView 그리기

void CMExDlgView::OnDraw(CDC* /*pDC*/)
{
	CMExDlgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMExDlgView 인쇄

BOOL CMExDlgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMExDlgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMExDlgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMExDlgView 진단

#ifdef _DEBUG
void CMExDlgView::AssertValid() const
{
	CView::AssertValid();
}

void CMExDlgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMExDlgDoc* CMExDlgView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMExDlgDoc)));
	return (CMExDlgDoc*)m_pDocument;
}
#endif //_DEBUG


// CMExDlgView 메시지 처리기


void CMExDlgView::OnDialogshow()
{
	CDlgTest* pDlg = new CDlgTest;
	pDlg->DoModal();
	delete pDlg;
}
