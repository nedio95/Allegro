#pragma once

#include "DynamicObject.h"

class Player : public DynamicObject
{

public:
	Player(float posX, float posY); //:DynamicObject(posX, posY)
	~Player();

	void UpdateLogic()override;

	void Jump();
	void h_Jump();

	void h_Gravity();

protected:

	void ApplyGravity()override;

	bool m_isJumping;

	float m_jumpHeight;
	float m_currentJumpStrenght;
	float m_jumpStrenght;
};

