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
#include "Manager_Time.h"

class GameObject
{
public:
	GameObject();
	GameObject(float posX, float posY);
	~GameObject();

	virtual void List_AddObject();

	float GetX();
	float GetY();

	void SetPos(float newX, float newY);
	void SetPosToObj(GameObject* obj);
	void ChangePos(float difX, float difZ);
	void ChangeX(float difX);
	void ChangeY(float difY);

	int GetSizeX();
	int GetSizeY();

	static void UpdateAllLogic();
	virtual void UpdateLogic();
	virtual void Render(int disX, int disY);

	static GameObject* GetHead();
	GameObject* GetNext();
	GameObject* GetPrevious();

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
	
	static enum DIRECTION
	{
		UP = -2,
		LEFT = -1,
		NONE = 0,
		RIGHT = 1,
		DOWN = 2,
	};
	
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

	bool m_hasCollision;
	bool Collision(int direction, bool perPixel);
	bool PixelPerfectCollision(GameObject* col);

	static GameObject* head_gameObject;
	static GameObject* tail_gameObject;

	GameObject* next_gameObject;
	GameObject* previous_gameObject;

	void RecycleObject();
};