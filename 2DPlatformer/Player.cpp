#include "Player.h"

Player::Player(float posX, float posY) :DynamicObject(posX, posY)
{
	LoadSkinSet("assets/Hero");

	m_speedHor = 64;
	m_jumpStrenght = 6.0 / 32; // 4 * 32;
	GravAcc = 9.8 / 32;
	GravAffected = true;
//	m_posX = 16;
}

Player::~Player()
{

}

void Player::UpdateLogic()
{
	
	if (GravAffected)
		ApplyGravity();
		
}
/*
void Player::LoadSkinSet()
{
	
		LoadSkin("assets/hero_stand.bmp");
}
*/

void Player::Jump()
{
	if (
		!Collision(UP, true)
		&&
		!m_isJumping
		)
	{
		m_posY -= 2;
		std::cout << "Jump initiated" << std::endl;
		m_isJumping = true;
		m_jumpHeight = 0;
		m_currentJumpStrenght = m_jumpStrenght;
	}
}

void Player::ApplyGravity()
{
	float finalVertVel = 0;
	float deltaTime = TimeManager::GetDT();
	m_vertVel = m_vertVel + (GravAcc * deltaTime);

	finalVertVel = m_vertVel;
	if (m_isJumping)
		finalVertVel -= m_jumpStrenght;

	if (finalVertVel > 0)
	{
		m_posY += 1;
		if (!Collision(DOWN, true)) //not col down
		{
			m_posY -= 1;
			TranslateVert(finalVertVel);
		}
		else
		{
			m_posY -= 1;
			//std::cout << "Grounded" << std::endl;
			m_vertVel = 0;
			m_isJumping = 0;
		}
	

	}
	else if (finalVertVel < 0)
	{
		m_posY -= 1;
		if (!Collision(UP, true)) //not col down
		{
			m_posY += 1;
			TranslateVert(finalVertVel);
		}
		else
		{
			m_posY += 1;
		//	m_vertVel = 0;
			m_isJumping = 0;
		}
		
	}


		//std::cout << "Update, grav should run " << m_posY << std::endl;

		
	//	std::cout << finalVertVel << std::endl;
		
		//m_currentGravAcc = m_currentGravAcc + (g_gravAcceleration * deltaTime);
	
		//std::cout << "Grounded" << std::endl;
	//if (m_vertVel != 0)
	//std::cout << m_vertVel << std::endl;
	
		
}