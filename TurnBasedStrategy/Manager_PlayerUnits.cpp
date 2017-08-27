#pragma once

#include "Manager_PlayerUnits.h"

UnitManager::UnitManager()
{
	m_currentlySelectedUnit = 0;
}

UnitManager::~UnitManager()
{

}

bool UnitManager::CheckUnitActions()
{
	if (m_units[m_currentlySelectedUnit]->GetActionsAvailability())
	{
		return true;
	}
	return false;
}

void UnitManager::ChangeUnit(int diff)
{
	m_currentlySelectedUnit += diff;

	if (m_currentlySelectedUnit < 0)
		m_currentlySelectedUnit = m_units.size()-1;
	else if ((unsigned)m_currentlySelectedUnit >= m_units.size())
		m_currentlySelectedUnit = 0;

//	HUDManager::ChangeSelUnit(m_units[m_currentlySelectedUnit]);

}

void UnitManager::MarkUnit()
{

}

void UnitManager::AddUnit(Unit* unit)
{
	m_units.push_back(unit);
}

float UnitManager::GetMarkerX()
{
	float returnThis = m_units[m_currentlySelectedUnit]->GetX();
	return returnThis;
}

float UnitManager::GetMarkerY()
{
	float returnThis = m_units[m_currentlySelectedUnit]->GetY();
	return returnThis;
}

Unit* UnitManager::GetSelUnit()
{
	return m_units[m_currentlySelectedUnit];
}

bool UnitManager::CheckPosForUnit(int checkX, int checkY)
{
	for (unsigned i = 0; i < m_units.size(); i++)
	{
		if (m_units[i]->IsAlive())
		{
			int x = m_units[i]->GetX() / 32;
			int y = m_units[i]->GetY() / 32;
			if ((x == checkX) && (y == checkY))
				return true;
		}
	}
	return false;

}

Unit* UnitManager::getUnitAtPos(int checkX, int checkY)
{
	for (unsigned i = 0; i < m_units.size(); i++)
	{
		if (m_units[i]->IsAlive())
		{
			int x = m_units[i]->GetX() / 32;
			int y = m_units[i]->GetY() / 32;
			if ((x == checkX) && (y == checkY))
				return m_units[i];
		}
	}
	return NULL;
}

void UnitManager::ResetTurn()
{
	for (unsigned i = 0; i < m_units.size(); i++)
	{
		if (m_units[i]->IsAlive())
		{
			m_units[i]->ResetPt();
		}
	}
}