
// MsgView.cpp: CMsgView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Msg.h"
#endif

#include "MsgDoc.h"
#include "MsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMsgView

IMPLEMENT_DYNCREATE(CMsgView, CView)

BEGIN_MESSAGE_MAP(CMsgView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_UNDO, &CMsgView::OnEditUndo)
END_MESSAGE_MAP()

// CMsgView 생성/소멸

CMsgView::CMsgView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMsgView::~CMsgView()
{
}

BOOL CMsgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMsgView 그리기

void CMsgView::OnDraw(CDC* /*pDC*/)
{
	CMsgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMsgView 인쇄

BOOL CMsgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMsgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMsgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMsgView 진단

#ifdef _DEBUG
void CMsgView::AssertValid() const
{
	CView::AssertValid();
}

void CMsgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMsgDoc* CMsgView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMsgDoc)));
	return (CMsgDoc*)m_pDocument;
}
#endif //_DEBUG


// CMsgView 메시지 처리기


void CMsgView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString temp;
	temp.Format(_T(" %c key press!!"), nChar);
	AfxMessageBox(temp);

	// 
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMsgView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	MessageBox(_T("Left Click Pressed"));


	CView::OnLButtonDown(nFlags, point);
}


void CMsgView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	MessageBox(_T("Right Click Pressed"));

	CView::OnRButtonDown(nFlags, point);
}


void CMsgView::OnEditUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Select the Menu Undo item"));

}
