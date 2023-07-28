#include "pch.h"
#include "CStraightLine.h"

CStraightLine::CStraightLine()
{
}

CStraightLine::CStraightLine(CPoint tpoint, int tlinethickness, COLORREF tlinecolor)
{
	point = tpoint;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
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
