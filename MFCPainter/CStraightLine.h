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

public:
	CStraightLine::CStraightLine();
	CStraightLine::CStraightLine(CPoint tpoint, int tlinethickness, COLORREF tlinecolor);
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
	void Draw(CStraightLine line, CDC memDC) {
		
	}
};
