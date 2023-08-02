#pragma once
#include "pch.h"
#include "framework.h"
#include "CElement.h"


class CFreeline : public CElement
{
protected:
	LONG x;
	LONG y;

	int linethickness;
	COLORREF linecolor;
	bool bline;

public:
	CFreeline::CFreeline(LONG x, LONG y, int linethickness, COLORREF linecolor, bool tbline);
	CFreeline::CFreeline(LONG x, LONG y, int linethickness, COLORREF linecolor);
	CFreeline(CFreeline& other);
	virtual ~CFreeline();
	int Getlinethickness();
	COLORREF Getlinecolor();
	LONG Getx();
	LONG Gety();
	bool Getbline();

	virtual string Save();
	void Draw(CDC &memDC);

};

