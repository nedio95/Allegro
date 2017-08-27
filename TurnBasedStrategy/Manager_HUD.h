#pragma once

#include <iostream>
#include <conio.h>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Unit.h"

class HUDManager
{
public:
	static HUDManager* CreateHUD();

	static HUDManager* GetHUD();

	void RenderHUD();

	void AddCoin();
	void PickCoin();
	void AddKey();
	void PickKey();
	bool AllKeysCollected();

	static void RenderUnitHp(int x, int y, int hp);
//	static void ChangeSelUnit(Unit* unit);
//	static void WTF(Unit* unit);
//	static Unit* m_selUnit;

private:
	HUDManager();
	~HUDManager();



	static HUDManager* s_HUD;

	ALLEGRO_FONT* font = NULL;

	int m_keys;
	int m_coins;
	int m_coinsMax;

	static ALLEGRO_FONT* m_font;
};