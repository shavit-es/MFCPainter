
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
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()

	ON_COMMAND_RANGE(ID_FREELINE, ID_ELLIPSE, OnChangeTool)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FREELINE, ID_ELLIPSE, OnUpdateChangeTool)
	ON_COMMAND(ID_LINECOLOR, &CMFCPainterView::OnLinecolor)
	ON_COMMAND(ID_FILLCOLOR, &CMFCPainterView::OnFillcolor)

//선 굵기 함수
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
	m_cptPoint = point;
	m_cptNewPoint = point;
	SetCapture();
	//버튼 클릭하면 시작 지점 설정(벡터에 추가)
	if (m_nType == ID_FREELINE && m_bNotDrawing) {
		m_vecElement.push_back(CFreeline(point, m_nLineThickness, m_ColorLine, false));
	}
	else if (m_nType == ID_LINE && m_bNotDrawing) {
		m_veCStraightLine.push_back(CStraightLine(point, m_nLineThickness, m_ColorLine));
		m_veCStraightLine.push_back(CStraightLine(point, m_nLineThickness, m_ColorLine));
		m_bNotDrawing = false;
	}
	else if (m_nType == ID_RECTANGLE && m_bNotDrawing) {
		m_vecRec.push_back(CRec(point.x, point.y, point.x, point.y, m_nLineThickness, m_ColorLine, m_ColorFill));
		m_bNotDrawing = false;
	}
	else if (m_nType == ID_ELLIPSE && m_bNotDrawing) {
		m_vecEll.push_back(CEll(point.x, point.y, point.x, point.y, m_nLineThickness, m_ColorLine, m_ColorFill));
		m_bNotDrawing = false;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMFCPainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	//마우스 누른 채로 드래그 할 때 없앴다가 생성하는 과정 반복
	if ((nFlags&&MK_LBUTTON) == MK_LBUTTON) {
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		if (m_nType == ID_FREELINE) {
			m_vecElement.push_back(CFreeline(point, m_nLineThickness, m_ColorLine));
			Invalidate(false);
		}
		else if (m_nType == ID_LINE && !m_bNotDrawing) {
			m_veCStraightLine.pop_back();
			m_veCStraightLine.push_back(CStraightLine(point, m_nLineThickness, m_ColorLine));
			Invalidate(false);
		}
		else if (m_nType == ID_RECTANGLE&&!m_bNotDrawing) {
			m_vecRec.pop_back();
			m_vecRec.push_back(CRec(m_cptPoint.x, m_cptPoint.y, point.x, point.y, m_nLineThickness, m_ColorLine, m_ColorFill));
			Invalidate(false);			
		}
		else if (m_nType == ID_ELLIPSE && !m_bNotDrawing) {
			m_vecEll.pop_back();
			m_vecEll.push_back(CEll(m_cptPoint.x, m_cptPoint.y, point.x, point.y, m_nLineThickness, m_ColorLine, m_ColorFill));
			Invalidate(false);
		}
		m_cptNewPoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCPainterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	CClientDC dc(this);
	CBrush brush, *pOldBrush;
	//마우스 뗄 때 그리고 있지 않음(bool)으로 할당
	if (m_nType == ID_FREELINE) {
		m_vecElement.push_back(CFreeline(point, m_nLineThickness, m_ColorLine,false));
	}
	else if (m_nType == ID_LINE) {
		m_bNotDrawing = true;
	}
	else if (m_nType == ID_RECTANGLE) {
		m_bNotDrawing = true;
	}
	else if (m_nType == ID_ELLIPSE) {
		m_bNotDrawing = true;
	}
	Invalidate(false);
	CView::OnLButtonUp(nFlags, point);
}




void CMFCPainterView::OnPaint()
{
	CPaintDC dc(this); 	
	CDC *pDC = &dc;

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	memDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	for (int i = 0; i < m_vecElement.size(); i++)
	{
		m_vecElement[i].Draw(memDC);
	}

	for (int j = 0; j < m_veCStraightLine.size(); j++)
	{
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, m_veCStraightLine[j].Getlinethickness(), m_veCStraightLine[j].Getlinecolor());
		pOldPen = (CPen *)memDC.SelectObject(&pen);
		if (j%2==0) {
			memDC.MoveTo(m_veCStraightLine[j].Getpoint().x, m_veCStraightLine[j].Getpoint().y);
		}
		else{
			memDC.LineTo(m_veCStraightLine[j].Getpoint().x, m_veCStraightLine[j].Getpoint().y);
		}
	}

	for (int i = 0; i < m_vecRec.size(); i++)
	{
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, m_vecRec[i].Getlinethickness(), m_vecRec[i].Getlinecolor());
		pOldPen = (CPen *)memDC.SelectObject(&pen);
		//내부 색을 색칠색으로
		brush.CreateSolidBrush(m_vecRec[i].Getfillcolor());
		pOldBrush = (CBrush *)memDC.SelectObject(brush);
		memDC.Rectangle(m_vecRec[i].Getx(), m_vecRec[i].Gety(), m_vecRec[i].Getxw(), m_vecRec[i].Getyh());
	}
	for (int j = 0; j < m_vecEll.size(); j++)
	{
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, m_vecEll[j].Getlinethickness(), m_vecEll[j].Getlinecolor());
		pOldPen = (CPen *)memDC.SelectObject(&pen);
		//내부 색을 색칠색으로
		brush.CreateSolidBrush(m_vecEll[j].Getfillcolor());
		pOldBrush = (CBrush *)memDC.SelectObject(brush);
		memDC.Ellipse(m_vecEll[j].Getx(), m_vecEll[j].Gety(), m_vecEll[j].Getxw(), m_vecEll[j].Getyh());
	}


	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bmp.DeleteObject();

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


