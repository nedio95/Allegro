#include "Manager_HUD.h"

HUDManager* HUDManager::s_HUD = NULL;
ALLEGRO_FONT* HUDManager::m_font = NULL; 
//Unit* HUDManager::m_selUnit = NULL;

HUDManager::HUDManager()
{
	font = al_load_ttf_font("assets/DejaVuSans.ttf", 15, 0);
	m_font = al_load_ttf_font("assets/DejaVuSans.ttf", 10, 0);

}

HUDManager::~HUDManager()
{

}

HUDManager* HUDManager::CreateHUD()
{
	if (s_HUD == NULL)
	{
		s_HUD = new HUDManager();
	}
	else
	{
		std::cout << "ERROR: HUD already exists" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		exit(1);
	}
	return s_HUD;
}

HUDManager* HUDManager::GetHUD()
{
	return s_HUD;
}

void HUDManager::RenderHUD()
{
	const char* keys;
	if (m_keys != 0)
		keys = "Goal: Search for keys!";
	else
		keys = "Goal: Go through the EXIT!";

	std::string coinsAsString = std::to_string(m_coins) + "/" + std::to_string(m_coinsMax);
	const char * coinsAsChar = coinsAsString.c_str();

	//al_draw_textf(font, al_map_rgb(255, 0, 0), 50, 10, 0, keys);
	//	al_draw_textf(font, al_map_rgb(0, 0, 255), 50, 40, 0, coinsAsChar);

/*	if (m_selUnit == NULL) return;

	int move = m_selUnit->GetMovePt();
	int atk = m_selUnit->GetAtkPt();

	std::cout << "render unit actons" << std::endl;

	std::string moveAsStr = std::to_string(move);
	const char * moveAsChar = moveAsStr.c_str();

	std::string atkAsStr = std::to_string(atk);
	const char * atkAsChar = atkAsStr.c_str();

	al_draw_textf(m_font, al_map_rgb(255, 0, 0), 50, 10, 0, moveAsChar);
	al_draw_textf(m_font, al_map_rgb(0, 0, 255), 50, 40, 0, atkAsChar);

	*/
}


void HUDManager::AddCoin()
{
	m_coinsMax += 1;
}

void HUDManager::PickCoin()
{
	m_coins += 1;
}

void HUDManager::AddKey()
{
	m_keys += 1;
}

void HUDManager::PickKey()
{
	m_keys -= 1;
}

bool HUDManager::AllKeysCollected()
{
//	std::cout << m_keys << std::endl;
	if (m_keys == 0)
	{
		//std::cout << "True returned" << std::endl;
		return true;
	}
		
	else
		return false;
}

void HUDManager::RenderUnitHp(int x, int y, int hp)
{
	std::string hpAsStr = std::to_string(hp);
	const char * hpAsChar = hpAsStr.c_str();

	float hp2 = hp;
	float g = hp2 / 100.0 * 255.0;

	al_draw_textf(m_font, al_map_rgb(0, g  , 0), x, y+22, 0, hpAsChar);
}
/*
void HUDManager::ChangeSelUnit(Unit* unit)
{
//	m_selUnit = unit;
}

void HUDManager::WTF(Unit* unit)
{

}

*/