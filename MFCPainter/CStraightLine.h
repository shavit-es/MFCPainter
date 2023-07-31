#pragma once
#include "pch.h"
#include "framework.h"
#include "CElement.h"


class CStraightLine : public CElement
{
private:
	CPoint point;
	int linethickness;
	COLORREF linecolor;
	bool bstart;

public:
	CStraightLine::CStraightLine();
	CStraightLine::CStraightLine(CPoint tpoint, int tlinethickness, COLORREF tlinecolor, bool bstart);
	CStraightLine(CStraightLine& other);
	virtual ~CStraightLine();
	int Getlinethickness() {
		return linethickness;
	};
	COLORREF Getlinecolor() {
		return linecolor;
	}
	CPoint Getpoint() {
		return point;
	}
	void Draw(CDC &memDC) {
		CPen pen, *pOldPen;
		CBrush brush, *pOldBrush;
		pen.CreatePen(PS_SOLID, Getlinethickness(), Getlinecolor());
		pOldPen = (CPen *)memDC.SelectObject(&pen);
		if (Getbstart()) {
			memDC.MoveTo(Getpoint());
		}
		else {
			memDC.LineTo(Getpoint());
		}
	}

	bool Getbstart() {
		return bstart;
	}
};
