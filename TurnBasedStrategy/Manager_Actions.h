#pragma once

#include <iostream>
#include <conio.h>

#include <allegro5/allegro.h>

#include "Manager_PlayerUnits.h"

#include "UIObject.h"
#include "SpecialShittyUIObject.h"

#include "Unit.h"

#include "UnitH.h"
#include "UnitHInfantry.h"

#include "UnitA.h"
#include "UnitAInfantry.h"



class ActionsManager
{
public:
	ActionsManager(UnitManager* thisUMan, UnitManager* otherUMan);
	~ActionsManager();
	void Render();
	void ChangeSelection(Unit* selUnit ,int diff, int mapx, int mapy);
	int ActionChosen();
	bool ExecuteAction(int difX, int difY);
	bool ExecuteMove(int difX, int difY);
	bool ExecuteAtk(int difX);
	bool CheckTargetsInRange();
	void UpdateTargetsInRange();

	void ChangeManagers(UnitManager* thisUMan, UnitManager* otherUMan);

	bool PerformAttack();
	
private:
	UnitManager* m_thisUManager;
	UnitManager* m_otherUManager;
	const static int m_numActions = 3;
	Unit* m_selUnit;
	UIObject* m_move[m_numActions];
	UIObject* m_selector;
	SpecObj* m_atkSelector;
	int m_currentSelection;
	std::vector<SpecObj*>m_highlights;
	std::vector<Unit*> m_targetsInRange;
	int m_cAtkSel;

	void HighlightAttack(int mapx, int mapy);
	void HighlightMove(int mapx, int mapy);
	void ClearHighlight();
	
	

	bool selectingAtkTarget;
};