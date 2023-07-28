#include "pch.h"
#include "CRec.h"

CRec::CRec(LONG tx, LONG ty, LONG txw, LONG tyh, int tlinethickness, COLORREF tlinecolor, COLORREF tfillcolor) {
	x = tx;
	y = ty;
	xw = txw;
	yh = tyh;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
	fillcolor = tfillcolor;
}

CRec::~CRec()
{
}

CRec::CRec(CRec & other)
{
	x = other.Getx();
	y = other.Gety();
	xw = other.Getxw();
	yh = other.Getyh();
	linethickness = other.Getlinethickness();
	linecolor = other.Getlinecolor();
	fillcolor = other.Getfillcolor();
}
