#pragma once

#include "Scene.h"
#include "Manager_Time.h"
#include "Manager_HUD.h"
#include "Manager_PlayerUnits.h"
#include "Manager_Actions.h"

#include "Terrain.h"
#include "UnitHInfantry.h"
#include "UnitAInfantry.h"

class StrategyLevel : public Scene
{
public:
	StrategyLevel(std::string levelNumber);
	~StrategyLevel();
	//void LoadLevel(int levelNumber);

	//	void RenderLevel();

	int UpdateLogic(InputManager* inputManager)override;
	void RenderScene()override;

private:
	
	void LoadMap(std::string levelNumber);
	void LoadUnits(std::string levelNumber);

	int ProcessInput(InputManager* inputManager);
	void RenderMap();
	void RenderUnits();
	void RenderUI();

	Terrain* m_mapGrid[22][15];
	std::vector<Unit*> m_unitsList;
	UnitManager* m_playerManagers[2];
	ActionsManager* m_actionsManager;
	int m_currentActivePlayer;
	int m_currentInactivePlayer;


	HUDManager* m_HUDManager;

	int m_mapSizeX;
	int m_mapSizeY;

	int m_blockSize;

	static enum GAMEPLAY_STATES
	{
		CHOSING_UNIT,
		CHOSING_ACTION,
		EXECUTING_MOVE,
		EXECUTING_ATK
	};

	int m_gameplayState;

	Unit* m_selectedUnit;

	UIObject* m_unitSelector;

	void state_CHOSING_UNIT();
	void state_CHOSING_ACTION();
	void state_EXECUTING_MOVE();
	void state_EXECUTING_ATK();

//	std::vector<GameObject*> m_terrainList;
};