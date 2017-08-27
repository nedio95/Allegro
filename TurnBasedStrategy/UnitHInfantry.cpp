#include "UnitHInfantry.h"

UnitHInfantry::UnitHInfantry(int posX, int posY) : UnitH(posX, posY)
{
	m_maxHealth = 100;
	m_currentHealth = m_maxHealth;
	m_atkPower = 55;

	m_maxAtkPoints = 3;
	m_maxMovePoints = 1;
	m_atkPoints = m_maxAtkPoints;
	m_movePoints = m_maxMovePoints;
	LoadSkinSet("assets/Hero");
}

UnitHInfantry::~UnitHInfantry()
{

}

void UnitHInfantry::UpdateLogic() 
{

}