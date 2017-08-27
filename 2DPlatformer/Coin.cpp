#include "Coin.h"

Coin::Coin(float posX, float posY) :PickUp(posX, posY)
{
	LoadSkinSet("assets/Coin");
	m_hasCollision = false;
	type = 1;
}

Coin::~Coin()
{
	HUDManager::GetHUD()->PickCoin();
	std::cout << "destructor called" << std::endl;
	for (unsigned i = 0; i < m_skin.size(); i++)
	{
		al_destroy_bitmap(m_skin[i]);
		m_skin[i] = nullptr;
	}

	RecycleObject();
}

void Coin::UpdateLogic()
{
	if (Collision(NONE, true))
	{
		delete this;
	}
}
