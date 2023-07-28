#include "pch.h"
#include "CFreeline.h"

CFreeline::CFreeline(CPoint tpoint, int tlinethickness, COLORREF tlinecolor, bool tbline)
{
	point = tpoint;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
	bline = tbline;
}

CFreeline::CFreeline(CPoint tpoint, int tlinethickness, COLORREF tlinecolor)
{
	point = tpoint;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
	bline = true;
}

CFreeline::CFreeline(CFreeline & other)
{
	point = other.Getpoint();
	linethickness = other.Getlinethickness();
	linecolor = other.Getlinecolor();
	bline = other.Getbline();
}

CFreeline::~CFreeline()
{
}
