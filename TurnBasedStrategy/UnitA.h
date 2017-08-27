#pragma once

#include "Unit.h"

class UnitA : public Unit
{
public:
	UnitA();
	UnitA(int posX, int posY);
	~UnitA();

	virtual void UpdateLogic();
};