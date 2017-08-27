#pragma once

#include "Manager_Actions.h"

ActionsManager::ActionsManager(UnitManager* thisUMan, UnitManager* otherUMan)
{
	m_thisUManager = thisUMan;
	m_otherUManager = otherUMan;

	m_currentSelection = 2;
	selectingAtkTarget = false;

	int x = 10, y = 10, d = 32, i = 0;

	m_move[i] = new UIObject(x, y + d*i, 'Z');
	i++;
	m_move[i] = new UIObject(x, y + d*i, 'X');
	i++;
	m_move[i] = new UIObject(x, y + d*i, 'C');
	
	m_selector = new UIObject(x, y + d*m_currentSelection, 'U');

	m_atkSelector = new SpecObj(0, 0, 'T');
	m_cAtkSel = 0;

	
}

ActionsManager::~ActionsManager()
{
	
}


void ActionsManager::Render()
{
	for (int i = 0; i < m_numActions; i++)
	{
		m_move[i]->Render(0, 0);
	}
	m_selector->Render(0, 0);

	for (unsigned i = 0; i < m_highlights.size(); i++)
	{
		m_highlights[i]->Render();
	}

	if (selectingAtkTarget)
		m_atkSelector->Render();
}

void ActionsManager::ChangeSelection(Unit* selUnit, int diff, int mapx, int mapy)
{

	ClearHighlight();

	m_selUnit = selUnit;

	int sel = m_currentSelection;
	sel += diff;

	if (sel < 0)
		sel = m_numActions - 1 ;
	else if ((unsigned)sel == m_numActions)
		sel = 0;

	m_selector->SetPosToObj(m_move[sel]);

	m_currentSelection = sel;

	if (sel == 0)
	{
		HighlightMove(mapx, mapy);
		std::cout << "Press [Enter] to start moving" << std::endl << std::endl;
	}
	if (sel == 1)
	{
		HighlightAttack(mapx, mapy);
		std::cout << "Press [Enter] to start attacking" << std::endl << std::endl;

	}
		
	if (sel == 2)
		std::cout << "Press [Enter] to chose a different unit" << std::endl << std::endl;
}

void ActionsManager::HighlightAttack(int mapx, int mapy)
{


	ClearHighlight();

	if (!m_selUnit->GetAtkPt())
	{
		std::cout << "No possible attacks" << std::endl << std::endl;
		return;
	}

	std::cout << "Possible attacks shown in Red" << std::endl << std::endl;
	int atkP = m_selUnit->GetAtkPtMax();

	//if (atkP == 0) return;

	int posX = m_selUnit->GetX() / 32;
	int posY = m_selUnit->GetY() / 32;

	for (int x = 0; x < mapx; x++)
	{
		int dx = abs(posX - x);
		if (dx <= atkP)
		{
			for (int y = 0; y < mapy; y++)
			{
				int dy = abs(posY - y);
				int dxsum = dx + dy;
				if (atkP >= dxsum && dxsum != 0)
				{
					if (m_otherUManager->CheckPosForUnit(x, y))
						m_highlights.push_back(new SpecObj(x * 32, y * 32, 'I'));
				}
			}
		}
	}
}

void ActionsManager::HighlightMove(int mapx, int mapy)
{

	ClearHighlight();

	int moveP = m_selUnit->GetMovePt();

	if (!moveP)
	{
		std::cout << "No possible moves" << std::endl << std::endl;
		return;
	}

	std::cout << "Possible movement shown in Green" << std::endl;
	std::cout << "Blocked movement shown in Red" << std::endl << std::endl;
	

	int posX = m_selUnit->GetX() / 32;
	int posY = m_selUnit->GetY() / 32;

	for (int x = 0; x < mapx; x++)
	{
		int dx = abs(posX - x);
		if (moveP >= dx)
		{
			for (int y = 0; y < mapy; y++)
			{
				int dy = abs(posY - y);
				int dxsum = dx + dy;
				if (moveP >= dxsum && dxsum != 0 )
				{
					bool canMoveThere = true;
					if (m_thisUManager->CheckPosForUnit(x, y)) canMoveThere = false;
					if(m_otherUManager->CheckPosForUnit(x, y)) canMoveThere = false;
					if (canMoveThere)
						m_highlights.push_back(new SpecObj(x * 32, y * 32, 'M'));
					else 
						m_highlights.push_back(new SpecObj(x * 32, y * 32, 'I'));
				}
			}
		}
	}
}

void ActionsManager::ClearHighlight()
{
	for (unsigned i = 0; i < m_highlights.size(); i++)
	{
		delete m_highlights[i];
	}
	m_highlights.clear();
}

int ActionsManager::ActionChosen()
{
	return m_currentSelection;
}

bool ActionsManager::ExecuteAction(int difX, int difY)
{
	if (m_currentSelection == 0)
	{
		if (!m_selUnit->GetMovePt() )
		{
			std::cout << "Not enough Move Points" << std::endl << std::endl;
			return false;
		}
		ExecuteMove(difX, difY);
	}
	else if (m_currentSelection == 1)
	{
		if (!m_selUnit->GetAtkPt())
		{
			std::cout << "Not enough Attack Points" << std::endl << std::endl;
			return false;
		}
		if (!CheckTargetsInRange())
		{
			return false;
		}
		ExecuteAtk(difX);
	}
	return true;
}

bool ActionsManager::ExecuteMove(int difX, int difY)
{
	

	int targetX = m_thisUManager->GetSelUnit()->GetX()/32 + difX;
	int targetY = m_thisUManager->GetSelUnit()->GetY()/32 + difY;

	bool canMoveThere = true;
	if (m_thisUManager->CheckPosForUnit(targetX, targetY)) canMoveThere = false;
	if (m_otherUManager->CheckPosForUnit(targetX, targetY)) canMoveThere = false;
	if (canMoveThere)
	{
		m_selUnit->SetPos(targetX * 32, targetY * 32);
		m_selUnit->DeductPoint(1);
		HighlightMove(22,15);
	}
	else
		std::cout << "This position is blocked" << std::endl << std::endl;
		

	return canMoveThere;

}

bool ActionsManager::ExecuteAtk(int difX)
{
	m_cAtkSel += difX;

	if (m_cAtkSel < 0)
		m_cAtkSel = m_targetsInRange.size()-1;
	else if ((unsigned)m_cAtkSel == m_targetsInRange.size())
		m_cAtkSel = 0;

	m_atkSelector->SetPos(m_targetsInRange[m_cAtkSel]->GetX(), m_targetsInRange[m_cAtkSel]->GetY());
	return true;
}

bool ActionsManager::CheckTargetsInRange()
{
	if (!m_selUnit->GetAtkPt())
	{
		std::cout << "No targets in range" << std::endl << std::endl;
		return false;
	}

	bool targettsInRange = false;
	int atkP = m_selUnit->GetAtkPtMax();

	//if (atkP == 0) return;

	int posX = m_selUnit->GetX() / 32;
	int posY = m_selUnit->GetY() / 32;

	for (int x = 0; x < 22; x++)
	{
		int dx = abs(posX - x);
		if (dx <= atkP)
		{
			for (int y = 0; y < 15; y++)
			{
				int dy = abs(posY - y);
				int dxsum = dx + dy;
				if (atkP >= dxsum && dxsum != 0)
				{
					if (m_otherUManager->CheckPosForUnit(x, y))
						targettsInRange = true;;
				}
			}
		}
	}
	if (!targettsInRange) std::cout << "No targets in range" << std::endl << std::endl;
	return targettsInRange;
}

void ActionsManager::UpdateTargetsInRange()
{
	m_targetsInRange.clear();

	bool targettsInRange = false;
	int atkP = m_selUnit->GetAtkPtMax();

	int posX = m_selUnit->GetX() / 32;
	int posY = m_selUnit->GetY() / 32;

	for (int x = 0; x < 22; x++)
	{
		int dx = abs(posX - x);
		if (dx <= atkP)
		{
			for (int y = 0; y < 15; y++)
			{
				int dy = abs(posY - y);
				int dxsum = dx + dy;
				if (atkP >= dxsum && dxsum != 0)
				{
					if (m_otherUManager->CheckPosForUnit(x, y))
					{
						m_targetsInRange.push_back(m_otherUManager->getUnitAtPos(x, y));
					}
				}
			}
		}
	}

	m_cAtkSel = 0;
	selectingAtkTarget = true;
	m_atkSelector->SetPos(m_targetsInRange[m_cAtkSel]->GetX(), m_targetsInRange[m_cAtkSel]->GetY());
}

bool ActionsManager::PerformAttack()
{
	/*
	int tarX = m_targetsInRange[m_cAtkSel]->GetX();
	int tarY = m_targetsInRange[m_cAtkSel]->GetY();

	int selX = m_selUnit->GetX();
	int selY = m_selUnit->GetY();

	int d = abs(tarX - selX + tarY - selY);
	*/
	std::cout << m_selUnit->GetAtkPt() << std::endl;
	m_selUnit->DeductPoint(0);

	m_targetsInRange[m_cAtkSel]->TakeDamage(m_selUnit->GetDamage());
	
	if (m_selUnit->GetAtkPt() != 0)
		return true;

	selectingAtkTarget = false;
	return false;
}

void ActionsManager::ChangeManagers(UnitManager* thisUMan, UnitManager* otherUMan)
{
	m_thisUManager = thisUMan;
	m_otherUManager = otherUMan;
}