#include "pch.h"
#include "CFreeline.h"

CFreeline::CFreeline(CPoint tpoint, int tlinethickness, COLORREF tlinecolor, bool tline)
{
	point = tpoint;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
	bline = tline;
}

CFreeline::CFreeline(CPoint tpoint, int tlinethickness, COLORREF tlinecolor)
{
	point = tpoint;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
	bline = true;
}
