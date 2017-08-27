#pragma once

#include <vector>
#include <iostream>
#include <conio.h>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Manager_HUD.h"

#include "dirent.h"
#include "Manager_Time.h"

class Unit
{
public:
	Unit();
	Unit(int posX, int posY);
	~Unit();

	virtual void List_AddObject();

	bool IsAlive();
	int GetX();
	int GetY();

	void SetPos(int newX, int newY);
	void ChangePos(int difX, int difZ);
	void ChangeX(int difX);
	void ChangeY(int difY);

	int GetSizeX();
	int GetSizeY();

	int GetAtkPt();
	int GetAtkPtMax();
	int GetMovePt();
	void ResetPt();

	void TakeDamage(int dmg);
	int GetDamage();

	void DeductPoint(bool whichpoint);

	bool GetActionsAvailability();

	static void UpdateAllLogic();
	virtual void UpdateLogic();
	virtual void Render();

	static Unit* GetHead();
	Unit* GetNext();
	Unit* GetPrevious();

	static enum OBJ_TYPE
	{
		EMPTY = '.',
		HUMAN_INFL = 'Q',
		ALIEN_INFL = 'A'
	};

	static void CleanObjectList();



protected:
	bool m_isAlive;
	bool m_race;
	int m_type;
	int m_currentHealth;
	int m_maxHealth;
	int m_atkPower;
	int m_atkPoints;
	int m_movePoints;
	int m_maxAtkPoints;
	int m_maxMovePoints;
	int actionPoints;
	int m_posX, m_posY;

	void LoadSkin(std::string bitmapDirectory);
	void LoadSkinSet(std::string skinsDirectory);
	std::vector<ALLEGRO_BITMAP*> m_skin;
	ALLEGRO_BITMAP* m_skinDead;
	unsigned m_currentFrame;

	static Unit* head_Unit;
	static Unit* tail_Unit;

	Unit* next_Unit;
	Unit* previous_Unit;

	void RecycleObject();
};