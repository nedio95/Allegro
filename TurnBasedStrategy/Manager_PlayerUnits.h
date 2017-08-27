#pragma once

#include <iostream>
#include <conio.h>

#include <allegro5/allegro.h>

#include "UIObject.h"

#include "Unit.h"

#include "UnitH.h"
#include "UnitHInfantry.h"

#include "UnitA.h"
#include "UnitAInfantry.h"

class UnitManager
{
public:
	UnitManager();
	~UnitManager();

	bool CheckUnitActions();
	void ChangeUnit(int diff);

	void AddUnit(Unit* unit);
	
	float GetMarkerX();
	float GetMarkerY();

	Unit* GetSelUnit();

	bool CheckPosForUnit(int checkX, int checkY);
	Unit* getUnitAtPos(int checkX, int CheckY);

	void ResetTurn();

private:

	std::vector<Unit*> m_units;
	int m_currentlySelectedUnit;

	void MarkUnit();
};