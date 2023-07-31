#include "pch.h"
#include "CElement.h"

CElement::CElement()
{
}

CElement::~CElement()
{
}

CElement::CElement(CElement & other)
{
	x = other.Getx();
	y = other.Gety();
	xw = other.Getxw();
	yh = other.Getyh();
	linethickness = other.Getlinethickness();
	linecolor = other.Getlinecolor();
	fillcolor = other.Getfillcolor();
	point = other.Getpoint();
}
