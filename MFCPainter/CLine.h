#pragma once
#include "pch.h"
#include "framework.h"

class CLine
{
private:
	CPoint point;
	int linethickness;
	COLORREF linecolor;

public:
	CLine::CLine(CPoint tpoint, int tlinethickness, COLORREF tlinecolor);

	int Getlinethickness() {
		return linethickness;
	};
	COLORREF Getlinecolor() {
		return linecolor;
	}

	CPoint Getpoint() {
		return point;
	}

};
