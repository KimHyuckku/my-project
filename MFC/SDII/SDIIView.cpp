
// SDIIView.cpp: CSDIIView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDII.h"
#endif

#include "SDIIDoc.h"
#include "SDIIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIIView

IMPLEMENT_DYNCREATE(CSDIIView, CView)

BEGIN_MESSAGE_MAP(CSDIIView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DRAWBOX, &CSDIIView::OnDrawbox)
END_MESSAGE_MAP()

// CSDIIView 생성/소멸

CSDIIView::CSDIIView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSDIIView::~CSDIIView()
{
}

BOOL CSDIIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDIIView 그리기

void CSDIIView::OnDraw(CDC* /*pDC*/)	//여기 주석처리한거 해제하고 사용
{
	CSDIIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.




}


// CSDIIView 인쇄

BOOL CSDIIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDIIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDIIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSDIIView 진단

#ifdef _DEBUG
void CSDIIView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIIDoc* CSDIIView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIIDoc)));
	return (CSDIIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIIView 메시지 처리기


void CSDIIView::OnDrawbox()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CPen cPen, * oldPen;
	cPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 255));
	CBrush cBrush, * oldBrush;
	cBrush.CreateSolidBrush(RGB(255, 255, 0));


	CDC* pDC = GetDC();
	oldPen = pDC->SelectObject(&cPen);
	oldBrush = pDC->SelectObject(&cBrush);

	pDC->Rectangle(CRect(10, 10, 100, 100));
	pDC->SelectObject(oldPen);
	cBrush.DeleteObject();

	cPen.DeleteObject();
	ReleaseDC(pDC);

}
