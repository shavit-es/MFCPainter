#pragma once
#include "pch.h"
#include "framework.h"
#include "CElement.h"


class CFreeline : public CElement
{
protected:
	CPoint point;

	int linethickness;
	COLORREF linecolor;
	bool bline;

public:
	CFreeline::CFreeline(CPoint tpoint, int linethickness, COLORREF linecolor, bool tbline);
	CFreeline::CFreeline(CPoint tpoint, int linethickness, COLORREF linecolor);
	CFreeline(CFreeline& other);
	virtual ~CFreeline();
	int Getlinethickness();
	COLORREF Getlinecolor();
	CPoint Getpoint();
	bool Getbline();

	void Draw(CDC &memDC);

};

