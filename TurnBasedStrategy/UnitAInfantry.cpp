#include "UnitAInfantry.h"

UnitAInfantry::UnitAInfantry(int posX, int posY) : UnitA(posX, posY)
{
	m_maxHealth = 100;
	m_currentHealth = m_maxHealth;
	m_atkPower = 25;

	m_maxAtkPoints = 1;
	m_maxMovePoints = 3;
	m_atkPoints = m_maxAtkPoints;
	m_movePoints = m_maxMovePoints;

	LoadSkinSet("assets/Monster");
}

UnitAInfantry::~UnitAInfantry()
{

}

void UnitAInfantry::UpdateLogic() 
{

}