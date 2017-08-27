#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "InputManager.h"
#include "Manager_Display.h"
#include "Manager_Time.h"

#include"Scene.h"
#include "Level_Strategy.h"
#include "MainMenu.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void Game();
	
private:
	bool InitialiseAllegro();
	void GameLoop();
	void ProcessEvents();
	void LogicUpdate();
	void RenderUpdate();

	//==========================
	//	Input & Timer Queues
	//==========================

	InputManager *m_inputManager = NULL;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue2 = NULL;

	TimeManager *m_timeManager = NULL;

	ALLEGRO_TIMER *timer = NULL;
	int m_framesPerSecond;

	ALLEGRO_EVENT_QUEUE *timer_event_queue = NULL;

	//==========================
	//	Display
	//==========================

	DisplayManager* display = NULL;

	
	//==========================
	//	Bitmaps
	//==========================

	ALLEGRO_BITMAP* bitmap = NULL;
	ALLEGRO_BITMAP* bitmap_trans = NULL;
	ALLEGRO_BITMAP* bit_Creature = NULL;

	//==========================
	//	Fonts
	//==========================

	ALLEGRO_FONT* small_font = NULL;
	ALLEGRO_FONT* big_font = NULL;

	//==========================
	//	Gamestates
	//==========================

	enum UPDATE_STATES
	{
		UPDATE_STATE_RENDER, UPDATE_STATE_LOGIC
	};

	UPDATE_STATES updateState = UPDATE_STATE_RENDER;



	//==========================
	//	Scene
	//==========================

	int CurrentGameState;

	Scene* CurrentScene;
	StrategyLevel* CurrentLevel;
	MainMenu* CurrentMenu;

	void LoadLevel(std::string levelNumber);

	//==========================
	//	Testing
	//==========================

	bool testBool;
	int testInt;
};