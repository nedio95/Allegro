#include "Key.h"

Key::Key(float posX, float posY) :PickUp(posX, posY)
{
	LoadSkinSet("assets/Key");
	m_hasCollision = false;
	type = 1;
}

Key::~Key()
{
	HUDManager::GetHUD()->PickKey();
	std::cout << "destructor called" << std::endl;
	for (unsigned i = 0; i < m_skin.size(); i++)
	{
		al_destroy_bitmap(m_skin[i]);
		m_skin[i] = nullptr;
	}

	RecycleObject();
}

void Key::UpdateLogic()
{
	if (Collision(NONE, true))
	{
		delete this;
	}
}
