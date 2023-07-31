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
