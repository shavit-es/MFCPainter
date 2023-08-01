
// MFCPainterView.h: CMFCPainterView 클래스의 인터페이스
//

#pragma once
#include <vector>
#include <iostream>

#include "CRec.h"
#include "CEll.h"
#include "CFreeline.h"
#include "CStraightLine.h"

using namespace std;

class CMFCPainterView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCPainterView() noexcept;
	DECLARE_DYNCREATE(CMFCPainterView)

	// 특성입니다.
public:
	CMFCPainterDoc* GetDocument() const;

	// 작업입니다.
public:
	CPoint m_cptPoint, m_cptNewPoint;
	vector<CElement*> m_vecpElement;
	int m_nType = ID_FREELINE;
	int m_nLineThickness = 1;
	bool m_bNotDrawing = true;
	//검은색으로 초기화
	COLORREF m_ColorLine = RGB(0,0,0);
	COLORREF m_ColorFill = RGB(255, 255, 255);
	COLORREF m_ColorLineXor = RGB(0^255,0^255,0^255);
	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// 구현입니다.
public:
	virtual ~CMFCPainterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	
	afx_msg void OnChangeTool(UINT wParam);
	afx_msg void OnUpdateChangeTool(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLinecolor();
	afx_msg void OnFillcolor();
	afx_msg void OnLt1();
	afx_msg void OnLt2();
	afx_msg void OnLt3();
	afx_msg void OnLt5();
	afx_msg void OnLt7();
	afx_msg void OnLt9();
	afx_msg void OnLt11();
};

#ifndef _DEBUG  // MFCPainterView.cpp의 디버그 버전
inline CMFCPainterDoc* CMFCPainterView::GetDocument() const
{
	return reinterpret_cast<CMFCPainterDoc*>(m_pDocument);
}
#endif

