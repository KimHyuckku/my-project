
// MFC1View.cpp: CMFC1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC1.h"
#endif

#include "MFC1Doc.h"
#include "MFC1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC1View

IMPLEMENT_DYNCREATE(CMFC1View, CView)

BEGIN_MESSAGE_MAP(CMFC1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFC1View 생성/소멸

CMFC1View::CMFC1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFC1View::~CMFC1View()
{
}

BOOL CMFC1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC1View 그리기

void CMFC1View::OnDraw(CDC* pDC)
{
	CMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CFont cFont, * oldFont;
	//폰트를 만든다.
	cFont.CreateFont(24, 12,//v,h size
		0, 0,//angle
		FW_DONTCARE,//bold
		FALSE,//italic
		FALSE,//under line
		FALSE,//STRIKEOUT pulg
		DEFAULT_CHARSET,//CHAR SET
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH, _T("궁서체"));
	//oldFont backup
	oldFont = pDC->SelectObject(&cFont);


	CString test = _T("Hello MFC SDI GDI interfate test!!.");
	pDC->TextOutW(0, 0, test);

	test.Format(_T("HORZRES(가로크기) = % d"),
		pDC->GetDeviceCaps(HORZRES));
	pDC->TextOut(0, 20, test);
	test.Format(_T("VERTRES(세로크기) = % d"),
		pDC->GetDeviceCaps(VERTRES));
	pDC->TextOut(0, 40, test);

	test = _T("DrawText Example");
		//set box area
		CRect rect = CRect(0, 60, 400, 100);
	//call DrawText function
	pDC->DrawText(test, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	test = _T("ExtTextOut Example");  //foreground color is blue
	pDC->SetTextColor(RGB(255, 0, 255));
	pDC->SetBkColor(RGB(255, 255, 0)); // background color is yellow
	pDC->ExtTextOut(0, 120, ETO_CLIPPED | ETO_OPAQUE, CRect(0, 120, 400, 200), test, NULL);


	//oldFont를 다시 설정한다.
	pDC->SelectObject(oldFont); // restore oldFont
	//delete current font
	cFont.DeleteObject();

}


// CMFC1View 인쇄

BOOL CMFC1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC1View 진단

#ifdef _DEBUG
void CMFC1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC1Doc* CMFC1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC1Doc)));
	return (CMFC1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC1View 메시지 처리기
