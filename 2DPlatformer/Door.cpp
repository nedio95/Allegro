#include "Door.h"

Door::Door(float posX, float posY) :StaticObject(posX, posY)
{
	LoadSkinSet("assets/Door");
	m_hasCollision = false;
}

Door::~Door()
{

}

void Door::UpdateLogic()
{
	if (Collision(NONE, true))
	{
		//std::cout << "Col" << std::endl;
		if (HUDManager::GetHUD()->AllKeysCollected())
			std::cout << "WIN" << std::endl;
	}
}
