#include "pch.h"
#include "CFreeline.h"

CFreeline::CFreeline(LONG tx, LONG ty,int tlinethickness, COLORREF tlinecolor, bool tbline)
{
	this->x = tx;
	this->y = ty;
	this->linethickness = tlinethickness;
	this->linecolor = tlinecolor;
	this->bline = tbline;
}

CFreeline::CFreeline(LONG tx, LONG ty, int tlinethickness, COLORREF tlinecolor)
{
	this->x = tx;
	this->y = ty;
	this->linethickness = tlinethickness;
	this->linecolor = tlinecolor;
	this->bline = true;
}

CFreeline::CFreeline(CFreeline & other)
{
	x = other.Getx();
	y = other.Gety();
	linethickness = other.Getlinethickness();
	linecolor = other.Getlinecolor();
	bline = other.Getbline();
}

CFreeline::~CFreeline()
{
}

int CFreeline::Getlinethickness() {
	return linethickness;
};
COLORREF CFreeline::Getlinecolor() {
	return linecolor;
}

LONG CFreeline::Getx() {
	return x;
}


LONG CFreeline::Gety() {
	return y;
}

bool CFreeline::Getbline() {
	return bline;
}

string CFreeline::Save()
{
	string s = "";
	s += "CFreeline\n";
	s += to_string(x) + "\n"; //형변환 해주어야함
	s += to_string(y) + "\n";
	s += to_string(linethickness) + "\n";
	s += to_string(linecolor) + "\n";
	s += to_string(bline) + "\n";

	return s;
}

void CFreeline::Draw(CDC &memDC) {
	CPen pen, *pOldPen;
	CBrush brush, *pOldBrush;
	pen.CreatePen(PS_SOLID, Getlinethickness(), Getlinecolor());
	pOldPen = (CPen *)memDC.SelectObject(&pen);
	if (!Getbline()) {
		memDC.MoveTo(Getx(), Gety());
	}
	memDC.LineTo(Getx(), Gety());
}
