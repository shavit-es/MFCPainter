#include "pch.h"
#include "CEll.h"

CEll::CEll(LONG tx, LONG ty, LONG txw, LONG tyh, int tlinethickness, COLORREF tlinecolor, COLORREF tfillcolor)
{
	x = tx;
	y = ty;
	xw = txw;
	yh = tyh;
	linethickness = tlinethickness;
	linecolor = tlinecolor;
	fillcolor = tfillcolor;
}

CEll::CEll(CEll & other)
{
	x = other.Getx();
	y = other.Gety();
	xw = other.Getxw();
	yh = other.Getyh();
	linethickness = other.Getlinethickness();
	linecolor = other.Getlinecolor();
	fillcolor = other.Getfillcolor();
}

CEll::CEll()
{
}

CEll::~CEll()
{
}

LONG CEll::Getx()
{
	return x;
}

LONG CEll::Gety() {
	return y;
}
LONG CEll::Getxw() {
	return xw;
}
LONG CEll::Getyh() {
	return yh;
}
int CEll::Getlinethickness() {
	return linethickness;
};
COLORREF CEll::Getlinecolor() {
	return linecolor;
}
COLORREF CEll::Getfillcolor() {
	return fillcolor;
}

void CEll::Draw(CDC &memDC) {
	CPen pen, *pOldPen;
	CBrush brush, *pOldBrush;
	pen.CreatePen(PS_SOLID, Getlinethickness(), Getlinecolor());
	pOldPen = (CPen *)memDC.SelectObject(&pen);
	//내부 색을 색칠색으로
	brush.CreateSolidBrush(Getfillcolor());
	pOldBrush = (CBrush *)memDC.SelectObject(brush);
	memDC.Ellipse(Getx(), Gety(), Getxw(), Getyh());
}

IMPLEMENT_SERIAL(CEll, CObject, 1);

void CEll::Serialize(CArchive & ar)
{
	{
		CObject::Serialize(ar);
		if (ar.IsStoring()) {
			ar << x;
			ar << y;
			ar << xw;
			ar << yh;
			ar << linethickness;
			ar << linecolor;
			ar << fillcolor;
		}
		else {
			ar >> x;
			ar >> y;
			ar >> xw;
			ar >> yh;
			ar >> linethickness;
			ar >> linecolor;
			ar >> fillcolor;
		}
	}
}
