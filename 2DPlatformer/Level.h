#pragma once

#include "Scene.h"
#include "Manager_Time.h"
#include "Manager_HUD.h"
/*
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
//#include <conio.h>

#include "GameObject.h"
#include "StaticObject.h"
*/
#include "Wall.h"
#include "Door.h"
#include "DynamicObject.h"
#include "Player.h"
#include "Monster_Patroling.h"
#include "Coin.h"
#include "Key.h"

class Level : public Scene
{
public:
	Level(std::string levelNumber);
	~Level();
	//void LoadLevel(int levelNumber);

//	void RenderLevel();

	int UpdateLogic(InputManager* inputManager)override;
	void RenderScene()override;

private:
	int ProcessInput(InputManager* inputManager);
	void ScrollScreen();

	std::vector <std::string> m_grid;
	Player* m_player;
	HUDManager* m_HUDManager;

	int m_LevelSizeX;
	int m_LevelSizeY;

	int m_blockSize;
};