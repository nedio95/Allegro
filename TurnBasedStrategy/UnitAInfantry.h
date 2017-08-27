#pragma once

#include "UnitA.h"

class UnitAInfantry : public UnitA
{
public:
	UnitAInfantry(int posX, int posY);
	~UnitAInfantry();

	virtual void UpdateLogic();
};