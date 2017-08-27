#pragma once

#include "PickUp.h"

class Key : public PickUp
{

public:
	Key(float posX, float posY)/* : GameObject(posX, posY)*/;
	~Key();

	void UpdateLogic()override;

protected:


};