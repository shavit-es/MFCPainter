#include "pch.h"
#include "CLine.h"

CLine::CLine(CPoint tpoint, int tlinethickness, COLORREF tlinecolor)
{
	point = tpoint;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
}
