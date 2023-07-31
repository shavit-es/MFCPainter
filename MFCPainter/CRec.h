#pragma once
#include "pch.h"
#include "framework.h"
#include "CElement.h"

class CRec : public CElement
{
private:
	LONG x, y, xw, yh;
	int linethickness;
	COLORREF linecolor, fillcolor;
	

public:
	CRec::CRec(LONG tx, LONG ty, LONG txw, LONG tyh, int tlinethickness, COLORREF tlinecolor, COLORREF tfillcolor);
	virtual ~CRec();
	CRec(CRec& other);

	LONG Getx();
	LONG Gety();
	LONG Getxw();
	LONG Getyh();
	int Getlinethickness();
	COLORREF Getlinecolor();
	COLORREF Getfillcolor();

	void Draw(CDC &memDC);
};


