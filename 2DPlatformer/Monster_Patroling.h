#pragma once

#include "DynamicObject.h"

class Monster_Patroling : public DynamicObject
{

public:
	Monster_Patroling(float posX, float posY)/*:DynamicObject(posX, posY)*/;
	~Monster_Patroling();

	void UpdateLogic()override;
	void Move();

protected:
	float m_patrolDist;
	int m_patrolDir;
	float m_currentPatrol;
};