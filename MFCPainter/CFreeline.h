#pragma once
#include "pch.h"
#include "framework.h"
#include "CElement.h"


class CFreeline : public CElement
{
private:
	CPoint point;
	int linethickness;
	COLORREF linecolor;
	bool bline;

public:
	CFreeline::CFreeline(CPoint tpoint, int linethickness, COLORREF linecolor, bool tbline);
	CFreeline::CFreeline(CPoint tpoint, int linethickness, COLORREF linecolor);
	CFreeline(CFreeline& other);
	virtual ~CFreeline();
	int Getlinethickness() {
		return linethickness;
	};
	COLORREF Getlinecolor() {
		return linecolor;
	}

	CPoint Getpoint() {
		return point;
	}

	bool Getbline() {
		return bline;
	}

	void Draw(CFreeline freeline, CDC &memDC) {
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, freeline.Getlinethickness(), freeline.Getlinecolor());
		pOldPen = (CPen *)memDC.SelectObject(&pen);
		if (!freeline.bline) {
			memDC.MoveTo(freeline.Getpoint().x, freeline.Getpoint().y);
		}
		memDC.LineTo(freeline.Getpoint().x, freeline.Getpoint().y);
	}
};

