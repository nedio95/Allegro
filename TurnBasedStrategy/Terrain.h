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

#include "GameObject.h"

#include "dirent.h"
#include "Manager_Time.h"

class Terrain : public GameObject
{
public:
	Terrain();
	Terrain(float posX, float posY, int type);
	~Terrain();

	void List_AddObject();

	void Render();

	static Terrain* GetHead();
	Terrain* GetNext();
	Terrain* GetPrevious();

	static enum OBJ_TYPE
	{
		EMPTY = '.',
		ROADV = 'Q',
		ROADH = 'W',
		ROADC = 'E',
		ROADBR = 'R',
		ROADTL = 'T',
		ROADJ = 'Y',
		FORESTL = 'A',
		FORESTC = 'S',
		FORESTR = 'D',
		HILLL = 'F',
		HILLC = 'G',
		HILLR = 'H',
		SWAMP = 'J'
	};

	static void CleanObjectList();

protected:

	char m_type;
	float m_posX, m_posY;
	bool m_passable;
	float m_cost;

	static Terrain* head_Terrain;
	static Terrain* tail_Terrain;

	Terrain* next_Terrain;
	Terrain* previous_Terrain;

	void RecycleObject();
};