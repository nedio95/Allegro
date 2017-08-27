#pragma once

#include <iostream>
#include <conio.h>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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

private:
	HUDManager();
	~HUDManager();

	static HUDManager* s_HUD;

	ALLEGRO_FONT* font = NULL;

	int m_keys;
	int m_coins;
	int m_coinsMax;
	
};