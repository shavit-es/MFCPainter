
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

#include "CSaveDialog.h"
#include "CLoadDialog.h"
#include "CNewDialog.h"

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
ON_COMMAND(ID_FILE_SAVE, &CMFCPainterView::OnFileSave)
ON_COMMAND(ID_FILE_OPEN, &CMFCPainterView::OnFileOpen)
ON_COMMAND(ID_FILE_NEW, &CMFCPainterView::OnFileNew)
ON_COMMAND(ID_LINETHICKNESS, &CMFCPainterView::OnLinethickness)
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
	do {
		CClientDC dc(this);
		m_cptPoint = point;
		m_cptNewPoint = point;
		SetCapture();
		//버튼 클릭하면 시작 지점 설정(벡터에 추가)
		if (m_nType == ID_FREELINE && m_bNotDrawing) {
			m_vecpElement.push_back(new CFreeline(point.x, point.y, m_nLineThick, m_ColorLine, false));
			m_bNotDrawing = false;
		}
		else if (m_nType == ID_LINE && m_bNotDrawing) {
			m_vecpElement.push_back(new CStraightLine(point.x, point.y, m_nLineThick, m_ColorLine, true));
			m_vecpElement.push_back(new CStraightLine(point.x, point.y, m_nLineThick, m_ColorLine, true));
			m_bNotDrawing = false;
		}
		else if (m_nType == ID_RECTANGLE && m_bNotDrawing) {
			m_vecpElement.push_back(new CRec(point.x, point.y, point.x, point.y, m_nLineThick, m_ColorLine, m_ColorFill));
			m_bNotDrawing = false;
		}
		else if (m_nType == ID_ELLIPSE && m_bNotDrawing) {
			m_vecpElement.push_back(new CEll(point.x, point.y, point.x, point.y, m_nLineThick, m_ColorLine, m_ColorFill));
			m_bNotDrawing = false;
		}
		CView::OnLButtonDown(nFlags, point);
	}while (false);
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
		if (m_nType == ID_FREELINE && !m_bNotDrawing) {
			m_vecpElement.push_back(new CFreeline(point.x, point.y, m_nLineThick, m_ColorLine));
			Invalidate(false);
		}
		else if (m_nType == ID_LINE && !m_bNotDrawing) {
			m_vecpElement.pop_back();
			m_vecpElement.push_back(new CStraightLine(point.x, point.y, m_nLineThick, m_ColorLine, false));
			Invalidate(false);
		}
		else if (m_nType == ID_RECTANGLE&&!m_bNotDrawing) {
			m_vecpElement.pop_back();
			m_vecpElement.push_back(new CRec(m_cptPoint.x, m_cptPoint.y, point.x, point.y, m_nLineThick, m_ColorLine, m_ColorFill));
			Invalidate(false);			
		}
		else if (m_nType == ID_ELLIPSE && !m_bNotDrawing) {
			m_vecpElement.pop_back();
			m_vecpElement.push_back(new CEll(m_cptPoint.x, m_cptPoint.y, point.x, point.y, m_nLineThick, m_ColorLine, m_ColorFill));
			Invalidate(false);
		}
		m_cptNewPoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCPainterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	do {
		ReleaseCapture();
		CClientDC dc(this);
		CBrush brush, *pOldBrush;
		//마우스 뗄 때 그리고 있지 않음(bool)으로 할당
		if (m_nType == ID_FREELINE) {
			m_vecpElement.push_back(new CFreeline(point.x, point.y, m_nLineThick, m_ColorLine, false));
			m_bNotDrawing = true;
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
	} while (false);
}




void CMFCPainterView::OnPaint()
{
	do {
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

		for (auto elem : m_vecpElement)
		{
			elem->Draw(memDC);
		}

		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();
		bmp.DeleteObject();
	} while (false);
}


void CMFCPainterView::OnLinecolor()
{
	do {
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK) {
			m_ColorLine = dlg.GetColor(); //선택한 색을 COLORREF로 return
			m_ColorLineXor = (RGB(GetRValue(m_ColorLine) ^ 255, GetGValue(m_ColorLine) ^ 255, GetBValue(m_ColorLine) ^ 255));
		}
	} while (false);
}


void CMFCPainterView::OnFillcolor()
{
	do {
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK) {
			m_ColorFill = dlg.GetColor();
		}
	} while (false);
}


void CMFCPainterView::OnLt1() { m_nLineThick = 1; }
void CMFCPainterView::OnLt2() { m_nLineThick = 2; }
void CMFCPainterView::OnLt3() { m_nLineThick = 3; }
void CMFCPainterView::OnLt5() { m_nLineThick = 5; }
void CMFCPainterView::OnLt7() { m_nLineThick = 7; }
void CMFCPainterView::OnLt9() { m_nLineThick = 9; }
void CMFCPainterView::OnLt11() { m_nLineThick = 11; }




void CMFCPainterView::OnFileSave()
{
	do {
		CSaveDialog dlg;
		if (dlg.DoModal() == IDOK) {
			std::ofstream fout;
			fout.open("data.ini");
			fout << m_vecpElement.size();
			fout << "\n";
			for (int i = 0; i < m_vecpElement.size(); i++) {
				fout << m_vecpElement[i]->Save();
			}
			fout.close();
		}
	} while (false);
}


void CMFCPainterView::OnFileOpen()
{
	do {
		CLoadDialog dlg;
		if (dlg.DoModal() == IDOK) {
			m_vecpElement.resize(0);
			std::ifstream in("data.ini");
			string line;
			getline(in, line);
			line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
			int nvecSize = stoi(line);
			while (getline(in, line)) {
				line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
				if (line == "CFreeline") {
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG x = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG y = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					int linethickness = stoi(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					COLORREF linecolor = stoi(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					bool bline = stoi(line);
					m_vecpElement.push_back(new CFreeline(x, y, linethickness, linecolor, bline));
				}
				else if (line == "CStraightLine") {
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG x = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG y = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					int linethickness = stoi(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					COLORREF linecolor = stoi(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					bool bstart = stoi(line);
					m_vecpElement.push_back(new CStraightLine(x, y, linethickness, linecolor, bstart));
				}
				else if (line == "CRec") {
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG x = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG y = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG xw = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG yh = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					int linethickness = stoi(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					COLORREF linecolor = stoi(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					COLORREF fillcolor = stoi(line);
					m_vecpElement.push_back(new CRec(x, y, xw, yh, linethickness, linecolor, fillcolor));
				}
				else if (line == "CEll") {
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG x = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG y = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG xw = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					LONG yh = stol(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					int linethickness = stoi(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					COLORREF linecolor = stoi(line);
					getline(in, line);
					line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
					COLORREF fillcolor = stoi(line);
					m_vecpElement.push_back(new CEll(x, y, xw, yh, linethickness, linecolor, fillcolor));
				}
			}
			Invalidate();
		}
	} while (false);
}


void CMFCPainterView::OnFileNew()
{
	do {
		CNewDialog dlg;
		if (dlg.DoModal() == IDOK) {
			m_vecpElement.resize(0);
			Invalidate();
		}
	} while (false);
}


void CMFCPainterView::OnLinethickness()
{
	do {
		
	} while (false);
}
