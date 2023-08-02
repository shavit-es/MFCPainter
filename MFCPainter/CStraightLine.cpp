#include "pch.h"
#include "CStraightLine.h"

CStraightLine::CStraightLine()
{
}

CStraightLine::CStraightLine(LONG tx, LONG ty, int tlinethickness, COLORREF tlinecolor, bool tbstart)
{
	x = tx;
	y = ty;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
	bstart = tbstart;
}

CStraightLine::CStraightLine(CStraightLine & other)
{
	x = other.Getx();
	y = other.Gety();
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
LONG CStraightLine::Getx() {
	return x;
}

LONG CStraightLine::Gety() {
	return y;
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
		memDC.MoveTo(Getx(), Gety());
	}
	else {
		memDC.LineTo(Getx(), Gety());
	}
}

string CStraightLine::Save()
{
	string s = "";
	s += "CStraightLine\n";
	s += to_string(x) + "\n"; //형변환 해주어야함
	s += to_string(y) + "\n";
	s += to_string(linethickness) + "\n";
	s += to_string(linecolor) + "\n";
	s += to_string(bstart) + "\n";

	return s;
}
