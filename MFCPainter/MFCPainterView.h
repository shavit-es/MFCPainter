﻿#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>

#include "CRec.h"
#include "CEll.h"
#include "CFreeline.h"
#include "CStraightLine.h"

using namespace std;

class CMFCPainterView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCPainterView() noexcept;
	DECLARE_DYNCREATE(CMFCPainterView);

	// 특성입니다.
public:
	CMFCPainterDoc* GetDocument() const;

	// 작업입니다.
public:
	CPoint m_cptPoint;
	vector<CElement*> m_vecpElement;
	int m_nType = ID_FREELINE;
	int m_nLineThickness = 1;
	bool m_bNotDrawing = true;
	COLORREF m_ColorLine = RGB(0,0,0);
	COLORREF m_ColorFill = RGB(255, 255, 255);

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
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnLinethickness();
};

#ifndef _DEBUG  // MFCPainterView.cpp의 디버그 버전
inline CMFCPainterDoc* CMFCPainterView::GetDocument() const
{
	return reinterpret_cast<CMFCPainterDoc*>(m_pDocument);
}
#endif

