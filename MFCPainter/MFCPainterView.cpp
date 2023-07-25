
// MFCPainterView.cpp: CMFCPainterView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCPainter.h"
#endif

#include "MFCPainterDoc.h"
#include "MFCPainterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCPainterView

IMPLEMENT_DYNCREATE(CMFCPainterView, CView)

BEGIN_MESSAGE_MAP(CMFCPainterView, CView)
	ON_WM_CONTEXTMENU()
	//	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//	ON_WM_LBUTTONUP()
	//ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMFCPainterView 생성/소멸

CMFCPainterView::CMFCPainterView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCPainterView::~CMFCPainterView()
{
}

BOOL CMFCPainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCPainterView 그리기

void CMFCPainterView::OnDraw(CDC* /*pDC*/)
{
	CMFCPainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

//void CMFCPainterView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CMFCPainterView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCPainterView 진단

#ifdef _DEBUG
void CMFCPainterView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPainterDoc* CMFCPainterView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPainterDoc)));
	return (CMFCPainterDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCPainterView 메시지 처리기


void CMFCPainterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	m_CPointpoint = point;
	m_CPointnewpoint = point;
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void CMFCPainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	if ((nFlags&&MK_LBUTTON) == MK_LBUTTON) {
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		m_nType = ID_DrawRectangle;
		if (m_nType == ID_DrawCurve) {
			pen.CreatePen(PS_SOLID, m_nPenThickness, m_ColorLine);
			pOldPen = (CPen *)dc.SelectObject(&pen);
			dc.MoveTo(m_CPointpoint.x, m_CPointpoint.y);
			dc.LineTo(point.x, point.y);
			m_CPointpoint = point;
			dc.SelectObject(pOldPen);
		}
		else if (m_nType == ID_DrawLine) {
			pen.CreatePen(PS_SOLID, 1, m_ColorXor);
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_XORPEN);
			pOldPen = (CPen *)dc.SelectObject(&pen);
			dc.MoveTo(m_CPointpoint.x, m_CPointpoint.y);
			dc.LineTo(m_CPointnewpoint.x, m_CPointnewpoint.y);
			dc.MoveTo(m_CPointpoint.x, m_CPointpoint.y);
			dc.LineTo(point.x, point.y);
			dc.SelectObject(pOldPen);

		}
		else if (m_nType == ID_DrawRectangle) {
			pen.CreatePen(PS_SOLID, 1, m_ColorXor);
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_XORPEN);
			pOldPen = (CPen *)dc.SelectObject(&pen);
			dc.Rectangle(m_CPointpoint.x, m_CPointpoint.y, point.x, point.y);
			dc.SelectObject(pOldPen);
		}
		else if (m_nType == ID_DrawCircle) {

			//펜생성
			pen.CreatePen(PS_SOLID, 1, m_ColorXor);
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_XORPEN);
			pOldPen = (CPen *)dc.SelectObject(&pen);
			dc.Ellipse(m_CPointpoint.x, m_CPointpoint.y, m_CPointnewpoint.x, m_CPointnewpoint.y);
			dc.Ellipse(m_CPointpoint.x, m_CPointpoint.y, point.x, point.y);
			dc.SelectObject(pOldPen);

		}

		m_CPointnewpoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCPainterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ReleaseCapture();
	CClientDC dc(this);
	CBrush brush, *pOldBrush;
	if (m_nType == ID_DrawRectangle) {

		brush.CreateSolidBrush(m_ColorFill);
		pOldBrush = (CBrush *)dc.SelectObject(brush);
		dc.Rectangle(m_CPointpoint.x, m_CPointpoint.y, point.x, point.y);

	}
	else if (m_nType == ID_DrawCircle) {
		brush.CreateSolidBrush(m_ColorFill);
		pOldBrush = (CBrush *)dc.SelectObject(brush);
		dc.Ellipse(m_CPointpoint.x, m_CPointpoint.y, point.x, point.y);
	}
	CView::OnLButtonUp(nFlags, point);
}


void CMFCPainterView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
}
