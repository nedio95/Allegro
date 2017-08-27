#include "DynamicObject.h"

DynamicObject::DynamicObject(float posX, float posY) :GameObject(posX, posY)
{
	GravAcc = 9.8/32;
}

DynamicObject::~DynamicObject()
{

}

void DynamicObject::UpdateLogic()
{
	
}

void DynamicObject::ApplyGravity()
{
	/*
	if (!Collision(DOWN)) //not col down
	{
		//std::cout << "Update, grav should run " << m_posY << std::endl;

		float deltaTime = TimeManager::GetDT();
		m_vertVel = m_vertVel + (GravAcc * deltaTime);

		TranslateVert(m_vertVel);
		//m_currentGravAcc = m_currentGravAcc + (g_gravAcceleration * deltaTime);
	}
	else
		m_vertVel = 0;
		*/
}

void DynamicObject::TranslateVert(float diffY)
{
	/*
	for (int i = 0; i < (int)abs(diffY); i++)
	{
		//Move by 1
	}
	*/
	float difY = abs(diffY);
	int normDiff = diffY / difY;

	if (m_hasCollision)
	if (Collision(normDiff * 2, true))
	{
		//std::cout << "Colision";
		return;
	}

	//	std::cout << "No colision";

	if (diffY < 1)
	{
		m_posY += diffY;
		if (m_hasCollision)
		if (Collision(normDiff * 2, true))
		{
			m_posY -= diffY;
			//std::cout << "Colision";
			return;
		}
		
		return;
	}



	for (int i = 0; i < (int)difY; i++)
	{
		m_posY += normDiff;
		if (m_hasCollision)
		if (Collision(normDiff * 2, true))
		{
			//std::cout << "Colision";
			m_posY -= normDiff;
			return;
		}
	}

}

//these two can be improved a lot
void DynamicObject::MoveLeft()
{
	float deltaTime = TimeManager::GetDT();
//	std::cout << "Moving Left ";
	TranslateHorizontal(-m_speedHor * deltaTime);
	//std::cout << std::endl;
}

void DynamicObject::MoveRight()
{
	float deltaTime = TimeManager::GetDT();
//	std::cout << "Moving Right ";
	TranslateHorizontal(m_speedHor * deltaTime);
	//std::cout << std::endl;
}

void DynamicObject::TranslateHorizontal(float diffX)
{
	float difX = abs(diffX);
	int normDiff = diffX / difX;

	if (m_hasCollision)
		if (Collision(normDiff, true))
		{
			//std::cout << "Colision";
			return;
		}

//	std::cout << "No colision";

	if (diffX < 1)
	{
		m_posX += diffX;
		if (m_hasCollision)
		if (Collision(normDiff, true))
		{
			m_posX -= diffX;
			//std::cout << "Colision";
			return;
		}
		return;
	}



	for (int i = 0; i < (int)difX; i++)
	{
		m_posX += normDiff;
		if (m_hasCollision)
		if (Collision(normDiff, true))
		{
			m_posX -= normDiff;
			//std::cout << "Colision";
			return;
		}
		
	}

}
