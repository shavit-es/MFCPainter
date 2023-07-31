#include "pch.h"
#include "CFreeline.h"

CFreeline::CFreeline(CPoint tpoint, int tlinethickness, COLORREF tlinecolor, bool tbline)
{
	this->point = tpoint;
	this->linethickness = tlinethickness;
	this->linecolor = tlinecolor;
	this->bline = tbline;
}

CFreeline::CFreeline(CPoint tpoint, int tlinethickness, COLORREF tlinecolor)
{
	this->point = tpoint;
	this->linethickness = tlinethickness;
	this->linecolor = tlinecolor;
	this->bline = true;
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

int CFreeline::Getlinethickness() {
	return linethickness;
};
COLORREF CFreeline::Getlinecolor() {
	return linecolor;
}

CPoint CFreeline::Getpoint() {
	return point;
}

bool CFreeline::Getbline() {
	return bline;
}

void CFreeline::Draw(CDC &memDC) {
	CPen pen, *pOldPen;
	CBrush brush, *pOldBrush;
	pen.CreatePen(PS_SOLID, Getlinethickness(), Getlinecolor());
	pOldPen = (CPen *)memDC.SelectObject(&pen);
	if (!Getbline()) {
		memDC.MoveTo(Getpoint().x, Getpoint().y);
	}
	memDC.LineTo(Getpoint().x, Getpoint().y);
}
