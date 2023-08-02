#pragma once
#include <afx.h>
#include <fstream>
#include <string>
using namespace std;
class CElement :public CObject
{
private:


public:
	CElement::CElement();
	virtual ~CElement();
	CElement(CElement& other);

	virtual void Draw(CDC &memCDC) {};
	virtual string Save() { return NULL; };
};

