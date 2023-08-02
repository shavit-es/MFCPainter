#pragma once
#include "pch.h"
#include "framework.h"
#include "CElement.h"


class CStraightLine : public CElement
{
private:
	LONG x;
	LONG y;
	int linethickness;
	COLORREF linecolor;
	bool bstart;

public:
	CStraightLine::CStraightLine();
	CStraightLine::CStraightLine(LONG x, LONG y, int tlinethickness, COLORREF tlinecolor, bool bstart);
	CStraightLine(CStraightLine& other);
	virtual ~CStraightLine();
	
	int Getlinethickness();
	COLORREF Getlinecolor();
	LONG Getx();
	LONG Gety();
	bool Getbstart();

	void Draw(CDC &memDC);
	virtual string Save();
};
