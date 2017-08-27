#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
//#include <conio.h>

#include "UIObject.h"
#include "InputManager.h"
#include "Manager_Display.h"

class Scene
{
public:
	Scene();
	~Scene();
	
	virtual void RenderScene();
	virtual int UpdateLogic(InputManager* inputManager);

	enum GAME_STATE_CHANGE
	{
		CONTINUE,
		MAIN_MENU,
		NEW_GAME,
		LOAD,
		QUIT,
		PAUSE
	};
	
protected:
	//GameManager *m_manager;

	std::vector<GameObject*> m_gameObjects;
	DisplayManager* m_Display;
	void CleanObjects();

};