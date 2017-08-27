#pragma once

#include <vector>
#include <iostream>
#include <conio.h>
#include <string>


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "dirent.h"

class HUDObject
{
public:
	HUDObject(float posX, float posY);
	~HUDObject();

	void List_AddObject();

	float GetX();
	float GetY();

	void SetPos(float newX, float newY);
	void ChangePos(float difX, float difZ);
	void ChangeX(float difX);
	void ChangeY(float difY);

	int GetSizeX();
	int GetSizeY();

	static void UpdateAllLogic();
	virtual void UpdateLogic();
	void Render(int disX, int disY);

	static HUDObject* GetHead();
	HUDObject* GetNext();
	HUDObject* GetPrevious();

	static enum OBJ_TYPE
	{
		EMPTY = '.',
		WALL = 'W',
		MONSTER_PATROL = 'B',
		PLAYER = 'P',
		COIN = 'C',
		KEY = 'K',
		DOOR = 'D'

	};

	static void CleanObjectList();

protected:
	//	int m_posX_px, m_posY_px;

	int type;
	float m_posX, m_posY;
	int meterToPixel;

	void LoadSkin(std::string bitmapDirectory);
	void LoadSystemSkin(std::string bitmapDirectory);
	void LoadSkinSet(std::string skinsDirectory);
	std::vector<ALLEGRO_BITMAP*> m_skin;
	std::vector<ALLEGRO_BITMAP*> m_systemSkin;
	unsigned m_currentFrame;

	static HUDObject* head_HUDObject;
	static HUDObject* tail_HUDObject;

	HUDObject* next_HUDObject;
	HUDObject* previous_HUDObject;

	void RecycleObject();
};