#pragma once
#include "pch.h"
#include "framework.h"
#include "CElement.h"
#include <fstream>

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
	LONG Getx();
	LONG Gety();
	LONG Getxw();
	LONG Getyh();
	int Getlinethickness();
	COLORREF Getlinecolor();
	COLORREF Getfillcolor();
	void Draw(CDC &memDC);

	virtual string Save();
};

