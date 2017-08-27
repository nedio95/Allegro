#include "Monster_Patroling.h"

Monster_Patroling::Monster_Patroling(float posX, float posY) :DynamicObject(posX, posY)
{
	LoadSkinSet("assets/Bat");
	GravAffected = false;
	m_speedHor = 32;
	m_patrolDist = 32;
	m_currentPatrol = 0;
	m_patrolDir = 1;
}

Monster_Patroling::~Monster_Patroling()
{

}

void Monster_Patroling::UpdateLogic()
{
	if (Collision(NONE, true))
		std::cout << "Game Over" << std::endl;

	Move();
}

void Monster_Patroling::Move()
{
	//std::cout << "called" << std::endl;
	float deltaTime = TimeManager::GetDT();
	float moveBy = m_patrolDir * m_speedHor * deltaTime;
	m_currentPatrol += moveBy;	

	TranslateHorizontal(moveBy);

	if (m_currentPatrol < -m_patrolDist)
		m_patrolDir = 1;
	else if (m_currentPatrol > m_patrolDist)
		m_patrolDir = -1;
}