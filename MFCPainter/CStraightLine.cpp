#include "pch.h"
#include "CStraightLine.h"

CStraightLine::CStraightLine()
{
}

CStraightLine::CStraightLine(CPoint tpoint, int tlinethickness, COLORREF tlinecolor, bool tbstart)
{
	point = tpoint;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
	bstart = tbstart;
}

CStraightLine::CStraightLine(CStraightLine & other)
{
	point = other.Getpoint();
	linethickness = other.Getlinethickness();
	linecolor = other.Getlinecolor();
}

CStraightLine::~CStraightLine()
{
}
