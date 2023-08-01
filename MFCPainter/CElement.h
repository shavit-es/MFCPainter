#pragma once
#include <afx.h>

class CElement :public CObject
{
	DECLARE_SERIAL(CElement);
private:


public:
	CElement::CElement();
	virtual ~CElement();
	CElement(CElement& other);

	virtual void Draw(CDC &memCDC) {};
	virtual void Serialize(CArchive& ar) {};

	
};

