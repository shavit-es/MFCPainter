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

LONG CRec::Getx() {
	return x;
}
LONG CRec::Gety() {
	return y;
}
LONG CRec::Getxw() {
	return xw;
}
LONG CRec::Getyh() {
	return yh;
}
int CRec::Getlinethickness() {
	return linethickness;
}
COLORREF CRec::Getlinecolor() {
	return linecolor;
}
COLORREF CRec::Getfillcolor() {
	return fillcolor;
}

void CRec::Draw(CDC &memDC) {
	CPen pen, *pOldPen;
	CBrush brush, *pOldBrush;
	pen.CreatePen(PS_SOLID, Getlinethickness(), Getlinecolor());
	pOldPen = (CPen *)memDC.SelectObject(&pen);
	//내부 색을 색칠색으로
	brush.CreateSolidBrush(Getfillcolor());
	pOldBrush = (CBrush *)memDC.SelectObject(brush);
	memDC.Rectangle(Getx(), Gety(), Getxw(), Getyh());
}

string CRec::Save()
{
	string s = "";
	s += "CRec\n";
	s += to_string(x) + "\n"; //형변환 해주어야함
	s += to_string(y) + "\n";
	s += to_string(xw) + "\n";
	s += to_string(yh) + "\n";
	s += to_string(linethickness) + "\n";
	s += to_string(linecolor) + "\n";
	s += to_string(fillcolor) + "\n";

	return s;
}
