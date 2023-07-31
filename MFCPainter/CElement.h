#pragma once
#include <afx.h>

class CElement :public CObject
{
private:


public:
	CElement::CElement();
	virtual ~CElement();
	CElement(CElement& other);

	virtual void Draw(CDC &memCDC) {};

};

