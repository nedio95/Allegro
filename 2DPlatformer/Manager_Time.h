#pragma once

#include <iostream>
#include <conio.h>

#include <allegro5/allegro.h>

class TimeManager
{
public:
	static TimeManager* CreateTime();

	static TimeManager* GetTime();

	static void UpdateDeltaTime();
	
	static float GetDT();

private:
	TimeManager();
	~TimeManager();

	

	static TimeManager* s_Time;

	float m_deltaTime;
	float m_lastTime;


};