#pragma once
#include <afx.h>

class CElement :public CObject
{
private:
	LONG x, y, xw, yh;
	int linethickness;
	COLORREF linecolor, fillcolor;
	CPoint point;
	bool bline;

public:
	CElement::CElement();
	virtual ~CElement();
	CElement(CElement& other);

	CPoint Getpoint() {
		return point;
	}
	bool Getbline() {
		return bline;
	}
	void Draw(CDC &memCDC) {
	}
	LONG Getx() {
		return x;
	}
	LONG Gety() {
		return y;
	}
	LONG Getxw() {
		return xw;
	}
	LONG Getyh() {
		return yh;
	}
	int Getlinethickness() {
		return linethickness;
	}
	COLORREF Getlinecolor() {
		return linecolor;
	}
	COLORREF Getfillcolor() {
		return fillcolor;
	}
};

