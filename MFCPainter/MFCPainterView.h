﻿
// MFCPainterView.h: CMFCPainterView 클래스의 인터페이스
//

#pragma once


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
	CPoint m_CPointpoint;
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
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFCPainterView.cpp의 디버그 버전
inline CMFCPainterDoc* CMFCPainterView::GetDocument() const
   { return reinterpret_cast<CMFCPainterDoc*>(m_pDocument); }
#endif
