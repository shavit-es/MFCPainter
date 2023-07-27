#pragma once
#include "pch.h"
#include "framework.h"

class CRec
{
private:
	LONG x, y, xw, yh;
	int linethickness;
	COLORREF linecolor, fillcolor;
	

public:
	CRec::CRec(LONG tx, LONG ty, LONG txw, LONG tyh, int tlinethickness, COLORREF tlinecolor, COLORREF tfillcolor);

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
	};
	COLORREF Getlinecolor() {
		return linecolor;
	}
	COLORREF Getfillcolor() {
		return fillcolor;
	}
};


