#pragma once

#include "StaticObject.h"
#include "Manager_HUD.h"

class Door : public StaticObject
{

public:
	Door(float posX, float posY)/*:StaticObject(posX, posY)*/;
	~Door();

	void UpdateLogic()override;

protected:

};