#pragma once

#include <iostream>
#include <conio.h>

#include <allegro5/allegro.h>

class DisplayManager
{
public:
	static DisplayManager* CreateDisplay();

	static DisplayManager* GetDisplay();
	static ALLEGRO_DISPLAY* GetAlDisplay();
	

	float GetPosX();
	float GetPosY();

	void SetX(float newX);
	void SetY(float newY);

	int GetSizeX();
	int GetSizeY();

private:
	DisplayManager();
	~DisplayManager();

	static DisplayManager* s_Display;

	static ALLEGRO_DISPLAY* m_display;

	float m_posX;
	float m_posY;
	int m_screenX;
	int m_screenY;
	int m_sizeX;
	int m_sizeY;
};