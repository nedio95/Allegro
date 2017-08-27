#pragma once

#include "UnitH.h"

class UnitHInfantry : public UnitH
{
public:
	UnitHInfantry(int posX, int posY);
	~UnitHInfantry();

	virtual void UpdateLogic()override;
};