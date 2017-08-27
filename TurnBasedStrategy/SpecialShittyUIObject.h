#pragma once

#include <vector>
#include <iostream>
#include <conio.h>
#include <string>
//#include <dirent.h>
//#include <windows.h>
//#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "dirent.h"

class SpecObj
{
public:
	SpecObj();
	SpecObj(float posX, float posY, char type);
	~SpecObj();

	void Render();


	float m_posX, m_posY;
	void SetPos(int x, int y);

	void LoadSkin(std::string bitmapDirectory);
	void LoadSkinSet(std::string skinsDirectory);
	std::vector<ALLEGRO_BITMAP*> m_skin;
	unsigned m_currentFrame;
};