#pragma once

#include "PickUp.h"

class Coin : public PickUp
{

public:
	Coin(float posX, float posY)/* : GameObject(posX, posY)*/;
	~Coin();

	void UpdateLogic()override;

protected:


};