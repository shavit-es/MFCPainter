
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
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()

	ON_COMMAND_RANGE(ID_FREELINE, ID_ELLIPSE, OnChangeTool)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FREELINE, ID_ELLIPSE, OnUpdateChangeTool)
	ON_COMMAND(ID_LINECOLOR, &CMFCPainterView::OnLinecolor)
	ON_COMMAND(ID_FILLCOLOR, &CMFCPainterView::OnFillcolor)
//	ON_UPDATE_COMMAND_UI(ID_FREELINE, &CMFCPainterView::OnUpdateFreeline)
ON_COMMAND(ID_LT1, &CMFCPainterView::OnLt1)
ON_COMMAND(ID_LT2, &CMFCPainterView::OnLt2)
ON_COMMAND(ID_LT3, &CMFCPainterView::OnLt3)
ON_COMMAND(ID_LT5, &CMFCPainterView::OnLt5)
ON_COMMAND(ID_LT7, &CMFCPainterView::OnLt7)
ON_COMMAND(ID_LT9, &CMFCPainterView::OnLt9)
ON_COMMAND(ID_LT11, &CMFCPainterView::OnLt11)
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

}


void CMFCPainterView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CMFCPainterView::OnChangeTool(UINT wParam)
{
	m_nType = GetCurrentMessage()->wParam;
}

void CMFCPainterView::OnUpdateChangeTool(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_nType == (int)pCmdUI->m_nID);
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
	if (m_nType == ID_LINE) {
		m_VecLine.push_back(CLine(m_CPointpoint, m_nLineThickness, m_ColorLine));
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMFCPainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	if ((nFlags&&MK_LBUTTON) == MK_LBUTTON) {
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		if (m_nType == ID_FREELINE) {
			m_VecFreeline.push_back(CFreeline(point, m_nLineThickness, m_ColorLine));
			Invalidate();
		}
		else if (m_nType == ID_LINE) {
			pen.CreatePen(PS_SOLID, m_nLineThickness, m_ColorLineXor);
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_XORPEN);
			pOldPen = (CPen *)dc.SelectObject(&pen);

			dc.MoveTo(m_CPointpoint.x, m_CPointpoint.y);
			dc.LineTo(m_CPointnewpoint.x, m_CPointnewpoint.y);

			dc.MoveTo(m_CPointpoint.x, m_CPointpoint.y);
			dc.LineTo(point.x, point.y);

			dc.SelectObject(pOldPen);
		}
		else if (m_nType == ID_RECTANGLE) {
			pen.CreatePen(PS_SOLID, m_nLineThickness, m_ColorLineXor);
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_XORPEN);
			pOldPen = (CPen *)dc.SelectObject(&pen);
			dc.Rectangle(m_CPointpoint.x, m_CPointpoint.y, m_CPointnewpoint.x, m_CPointnewpoint.y);
			dc.Rectangle(m_CPointpoint.x, m_CPointpoint.y, point.x, point.y);
			dc.SelectObject(pOldPen);
		}
		else if (m_nType == ID_ELLIPSE) {
			//펜생성
			pen.CreatePen(PS_SOLID, m_nLineThickness, m_ColorLineXor);
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
	if (m_nType == ID_FREELINE) {
		m_VecFreeline.push_back(CFreeline(point, m_nLineThickness, m_ColorLine,false));
	}
	else if (m_nType == ID_LINE) {
		m_VecLine.push_back(CLine(point, m_nLineThickness, m_ColorLine));
	}
	else if (m_nType == ID_RECTANGLE) {
		m_VecRec.push_back(CRec(m_CPointpoint.x, m_CPointpoint.y, point.x, point.y, m_nLineThickness, m_ColorLine, m_ColorFill));
	}
	else if (m_nType == ID_ELLIPSE) {
		m_VecEll.push_back(CEll(m_CPointpoint.x, m_CPointpoint.y, point.x, point.y, m_nLineThickness, m_ColorLine, m_ColorFill));
	}
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}




void CMFCPainterView::OnPaint()
{
	CPaintDC dc(this); 	
	for (int i = 1; i < m_VecFreeline.size(); i++)
	{
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, m_VecFreeline[i].Getlinethickness(), m_VecFreeline[i].Getlinecolor());
		pOldPen = (CPen *)dc.SelectObject(&pen);
		if (i == 1) {
			dc.MoveTo(m_VecFreeline[0].Getpoint().x, m_VecFreeline[0].Getpoint().y);
		}else if (m_VecFreeline[i-1].Getbline()) {
			dc.LineTo(m_VecFreeline[i].Getpoint().x, m_VecFreeline[i].Getpoint().y);
		}
		dc.MoveTo(m_VecFreeline[i].Getpoint().x, m_VecFreeline[i].Getpoint().y);
		
	}

	for (int j = 0; j < m_VecLine.size(); j++)
	{
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, m_VecLine[j].Getlinethickness(), m_VecLine[j].Getlinecolor());
		pOldPen = (CPen *)dc.SelectObject(&pen);
		if (j%2==0) {
			dc.MoveTo(m_VecLine[j].Getpoint().x, m_VecLine[j].Getpoint().y);
		}
		else{
			dc.LineTo(m_VecLine[j].Getpoint().x, m_VecLine[j].Getpoint().y);
		}
	}

	for (int i = 0; i < m_VecRec.size(); i++)
	{
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, m_VecRec[i].Getlinethickness(), m_VecRec[i].Getlinecolor());
		pOldPen = (CPen *)dc.SelectObject(&pen);
		//내부 색을 색칠색으로
		brush.CreateSolidBrush(m_VecRec[i].Getfillcolor());
		pOldBrush = (CBrush *)dc.SelectObject(brush);
		dc.Rectangle(m_VecRec[i].Getx(), m_VecRec[i].Gety(), m_VecRec[i].Getxw(), m_VecRec[i].Getyh());
	}
	for (int j = 0; j < m_VecEll.size(); j++)
	{
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, m_VecEll[j].Getlinethickness(), m_VecEll[j].Getlinecolor());
		pOldPen = (CPen *)dc.SelectObject(&pen);
		//내부 색을 색칠색으로
		brush.CreateSolidBrush(m_VecEll[j].Getfillcolor());
		pOldBrush = (CBrush *)dc.SelectObject(brush);
		dc.Ellipse(m_VecEll[j].Getx(), m_VecEll[j].Gety(), m_VecEll[j].Getxw(), m_VecEll[j].Getyh());
	}
}


void CMFCPainterView::OnLinecolor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_ColorLine = dlg.GetColor(); //선택한 색을 COLORREF로 return
		m_ColorLineXor = (RGB(GetRValue(m_ColorLine) ^ 255, GetGValue(m_ColorLine) ^ 255, GetBValue(m_ColorLine) ^ 255));
	}
}


void CMFCPainterView::OnFillcolor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_ColorFill = dlg.GetColor();
	}
}


void CMFCPainterView::OnLt1() { m_nLineThickness = 1; }
void CMFCPainterView::OnLt2() { m_nLineThickness = 2; }
void CMFCPainterView::OnLt3() { m_nLineThickness = 3; }
void CMFCPainterView::OnLt5() { m_nLineThickness = 5; }
void CMFCPainterView::OnLt7() { m_nLineThickness = 7; }
void CMFCPainterView::OnLt9() { m_nLineThickness = 9; }
void CMFCPainterView::OnLt11() { m_nLineThickness = 11; }