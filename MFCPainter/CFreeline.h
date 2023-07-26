#pragma once
#include "pch.h"
#include "framework.h"

class CFreeline
{
private:
	CPoint point;
	int linethickness;
	COLORREF linecolor;
	bool bline;

public:
	CFreeline::CFreeline(CPoint tpoint, int linethickness, COLORREF linecolor, bool tline);
	CFreeline::CFreeline(CPoint tpoint, int linethickness, COLORREF linecolor);

	int Getlinethickness() {
		return linethickness;
	};
	COLORREF Getlinecolor() {
		return linecolor;
	}

	CPoint Getpoint() {
		return point;
	}

	bool Getbline() {
		return bline;
	}
};

