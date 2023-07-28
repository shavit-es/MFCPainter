#pragma once
#include "pch.h"
#include "framework.h"
#include "CElement.h"

class CEll : public CElement
{
private:
	LONG x, y, xw, yh;
	int linethickness;
	COLORREF linecolor, fillcolor;


public:
	CEll::CEll(LONG tx, LONG ty, LONG txw, LONG tyh, int tlinethickness, COLORREF tlinecolor, COLORREF tfillcolor);
	CEll::CEll(CEll & other);

	virtual ~CEll();

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

