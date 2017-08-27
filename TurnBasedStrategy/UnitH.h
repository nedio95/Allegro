#pragma once

#include "Unit.h"

class UnitH : public Unit
{
public:
	UnitH();
	UnitH(int posX, int posY);
	~UnitH();

	virtual void UpdateLogic()override;
};