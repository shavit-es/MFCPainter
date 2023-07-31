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
	
	int Getlinethickness();
	COLORREF Getlinecolor();
	CPoint Getpoint();
	bool Getbstart();

	void Draw(CDC &memDC);

};
