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

int CStraightLine::Getlinethickness() {
	return linethickness;
};
COLORREF CStraightLine::Getlinecolor() {
	return linecolor;
}
CPoint CStraightLine::Getpoint() {
	return point;
}
bool CStraightLine::Getbstart() {
	return bstart;
}

void CStraightLine::Draw(CDC &memDC) {
	CPen pen, *pOldPen;
	CBrush brush, *pOldBrush;
	pen.CreatePen(PS_SOLID, Getlinethickness(), Getlinecolor());
	pOldPen = (CPen *)memDC.SelectObject(&pen);
	if (Getbstart()) {
		memDC.MoveTo(Getpoint());
	}
	else {
		memDC.LineTo(Getpoint());
	}
}