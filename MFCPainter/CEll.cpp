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
	//���� ���� ��ĥ������
	brush.CreateSolidBrush(Getfillcolor());
	pOldBrush = (CBrush *)memDC.SelectObject(brush);
	memDC.Ellipse(Getx(), Gety(), Getxw(), Getyh());
}

string CEll::Save()
{
	string s = "";
	s += "CEll\n";
	s += to_string(x) + "\n"; //����ȯ ���־����
	s += to_string(y) + "\n";
	s += to_string(xw) + "\n";
	s += to_string(yh) + "\n";
	s += to_string(linethickness) + "\n";
	s += to_string(linecolor) + "\n";
	s += to_string(fillcolor) + "\n";

	return s;
}
