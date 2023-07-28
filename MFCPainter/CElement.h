#pragma once
#include <afx.h>

class CElement :public CObject
{
private:

public:
	CElement::CElement();
	virtual ~CElement();
	CElement(CElement& other);

	CPoint Getpoint() {
	}
	bool Getbline() {
	}
	void Draw(CDC &memCDC) {
	}
	LONG Getx() {
	}
	LONG Gety() {
	}
	LONG Getxw() {
	}
	LONG Getyh() {
	}
	int Getlinethickness() {
	}
	COLORREF Getlinecolor() {
	}
	COLORREF Getfillcolor() {
	}
};

