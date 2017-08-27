
#pragma once

#include "Level_Strategy.h"

StrategyLevel::StrategyLevel(std::string levelNumber)
{
	m_mapSizeX = 0;
	m_mapSizeY = 0;

	m_blockSize = 32;
	m_currentActivePlayer = 0;
	m_currentInactivePlayer = 1;

	m_playerManagers[m_currentActivePlayer] = new UnitManager();
	m_playerManagers[m_currentInactivePlayer] = new UnitManager();
	m_actionsManager = new ActionsManager(m_playerManagers[m_currentActivePlayer], m_playerManagers[m_currentInactivePlayer]);

	LoadMap(levelNumber);
	LoadUnits(levelNumber);

	

	m_selectedUnit = Unit::GetHead();
	state_CHOSING_UNIT();

	m_unitSelector = new UIObject(0, 0, 'U');

	


	m_HUDManager = HUDManager::CreateHUD();
}

StrategyLevel::~StrategyLevel()
{

}

void StrategyLevel::LoadMap(std::string levelNumber)
{
	std::string StrategyLevelToLoad = "StrategyLevels/Level" + levelNumber + "_terrain.txt";
	std::string line;
	std::ifstream infile(StrategyLevelToLoad);

	if (infile.is_open()) // if file has correctly opened
	{
		int y = 0;
		do
		{
			getline(infile, line); // extract one line of file into string
			//std::cout << line << std::endl;  // and display it
			//arenaToFill->LoadArenaRow(line);
			//m_grid.push_back(line);
			for (unsigned x = 0; x < line.size(); x++)
			{
				if ((int)x > m_mapSizeX)
				{
					m_mapSizeX = x;
				}

				if (line[x] != Terrain::EMPTY)
				{
					m_mapGrid[x][y] = new Terrain((float)x * 32, (float)y * 32, line[x]);
				}
			}
			y++;

		} while (!infile.eof()); // until the end of file (EOF) is reached

		infile.close(); // always close streams once finished

		m_mapSizeX *= m_blockSize;
		m_mapSizeY = y * m_blockSize;

	}
	else
	{
		std::cout << "Error opening map file for input" << std::endl << "Press any key to exit";
		_getch();
		exit(1);
	}
}

void StrategyLevel::LoadUnits(std::string levelNumber)
{
	std::string StrategyLevelToLoad = "StrategyLevels/Level" + levelNumber + "_units.txt";
	std::string line;
	std::ifstream infile(StrategyLevelToLoad);

	if (infile.is_open()) // if file has correctly opened
	{
		int y = 0;
		do
		{
			getline(infile, line); // extract one line of file into string
			//std::cout << line << std::endl;  // and display it
			//arenaToFill->LoadArenaRow(line);
			//m_grid.push_back(line);
			for (unsigned x = 0; x < line.size(); x++)
			{
				Unit* temp;
				if (line[x] == Unit::HUMAN_INFL)
				{
					temp = new UnitHInfantry((float)x * 32, (float)y * 32);
					m_unitsList.push_back(temp);
					m_playerManagers[0]->AddUnit(temp);
					temp = nullptr;
				}
				else if (line[x] == Unit::ALIEN_INFL)
				{
					temp = new UnitAInfantry((float)x * 32, (float)y * 32);
					m_unitsList.push_back(temp);
					m_playerManagers[1]->AddUnit(temp);
					temp = nullptr;
				}
			}
			y++;

		} while (!infile.eof()); // until the end of file (EOF) is reached

		infile.close(); // always close streams once finished
	}
	else
	{
		std::cout << "Error opening map file for input" << std::endl << "Press any key to exit";
		_getch();
		exit(1);
	}
}

int StrategyLevel::UpdateLogic(InputManager* inputManager)
{
	int returnThis = ProcessInput(inputManager);

	if (GameObject::GetHead() != NULL)
	{
		GameObject::UpdateAllLogic();
	}

	return returnThis;

}

void StrategyLevel::RenderScene()
{

	RenderMap();
	RenderUnits();
	RenderUI();
	

	m_HUDManager->RenderHUD();

}

void StrategyLevel::RenderMap()
{
	for (int x = 0; x < m_mapSizeX/32; x++)
	{
		for (int y = 0; y < m_mapSizeY/32; y++)
		{
			if (m_mapGrid[x][y] != NULL)
			{
				m_mapGrid[x][y]->Render();
			}
		}
	}
}

void StrategyLevel::RenderUnits()
{
	//std::cout << "Units are being rendered" << std::endl;
	if (Unit::GetHead() == NULL) return;

	Unit* drawObject = Unit::GetHead();

	drawObject->Render();

	while (drawObject->GetNext() != NULL)
	{
		drawObject = drawObject->GetNext();
		drawObject->Render();

	}
}

void StrategyLevel::RenderUI()
{
	m_unitSelector->SetPos(m_playerManagers[m_currentActivePlayer]->GetMarkerX(), m_playerManagers[m_currentActivePlayer]->GetMarkerY());
	m_unitSelector->Render(0,0);

	if (m_actionsManager != NULL)
	{
		m_actionsManager->Render();
	}

	if (m_gameplayState == CHOSING_ACTION)
	{
		if (GameObject::GetHead() == NULL) return;

		GameObject* drawObject = GameObject::GetHead();

		drawObject->Render(m_Display->GetPosX(), m_Display->GetPosY());

		while (drawObject->GetNext() != NULL)
		{
			drawObject = drawObject->GetNext();
			drawObject->Render(m_Display->GetPosX(), m_Display->GetPosY());

		}
	}

}

int StrategyLevel::ProcessInput(InputManager* inputManager)
{
	if (inputManager->GetPress(InputManager::KEY_Q))
	{
		std::cout << "Turn Ended ! Player Changed !" << std::endl;
		if (m_currentActivePlayer == 0)
		{
			m_currentActivePlayer = 1;
			m_currentInactivePlayer = 0;
		
		}
		else
		{
			m_currentActivePlayer = 0;
			m_currentInactivePlayer = 1;
		}

		m_playerManagers[0]->ResetTurn();
		m_playerManagers[1]->ResetTurn();
		m_actionsManager->ChangeManagers(m_playerManagers[m_currentActivePlayer], m_playerManagers[m_currentInactivePlayer]);

		state_CHOSING_UNIT();
	}

	if (inputManager->GetPress(InputManager::KEY_W))
	{
		if (m_gameplayState == CHOSING_ACTION)
		{
			m_actionsManager->ChangeSelection(m_playerManagers[m_currentActivePlayer]->GetSelUnit(), -1, m_mapSizeX / 32, m_mapSizeY / 32);
		}
		else if (m_gameplayState == EXECUTING_MOVE)
		{
			if (!m_actionsManager->ExecuteAction(0, -1)) state_CHOSING_ACTION();
		}
	}

	if (inputManager->GetPress(InputManager::KEY_S))
	{
		if (m_gameplayState == CHOSING_ACTION)
		{
			m_actionsManager->ChangeSelection(m_playerManagers[m_currentActivePlayer]->GetSelUnit(), 1, m_mapSizeX / 32, m_mapSizeY / 32);
		}
		else if (m_gameplayState == EXECUTING_MOVE)
		{
			if (!m_actionsManager->ExecuteAction(0, 1)) state_CHOSING_ACTION();
		}
	}

	if (inputManager->GetPress(InputManager::KEY_A))
	{
		switch (m_gameplayState)
		{
		case CHOSING_UNIT:
			m_playerManagers[m_currentActivePlayer]->ChangeUnit(-1);
			break;
		case EXECUTING_MOVE:
			if (!m_actionsManager->ExecuteAction(-1, 0)) state_CHOSING_ACTION();
			break;
		case EXECUTING_ATK:
			if (!m_actionsManager->ExecuteAction(-1, 0)) state_CHOSING_ACTION();
			break;
		}
	}

	if (inputManager->GetPress(InputManager::KEY_D))
	{
		switch (m_gameplayState)
		{
		case CHOSING_UNIT:
			m_playerManagers[m_currentActivePlayer]->ChangeUnit(1);
			break;
		case EXECUTING_MOVE:
			if (!m_actionsManager->ExecuteAction(1, 0)) state_CHOSING_ACTION();
			break;
		case EXECUTING_ATK:
			if (!m_actionsManager->ExecuteAction(1, 0)) state_CHOSING_ACTION();
			break;
		}
		
	}

	if (inputManager->GetPress(InputManager::KEY_ENTER))
	{
		if (m_gameplayState == CHOSING_UNIT)
		{
			if (m_playerManagers[m_currentActivePlayer]->CheckUnitActions())
				state_CHOSING_ACTION();
		}
		else if (m_gameplayState == CHOSING_ACTION)
		{
			int t = m_actionsManager->ActionChosen();
			if (t == 0)
				state_EXECUTING_MOVE();
			else if (t == 1)
			{
				if (m_actionsManager->CheckTargetsInRange())
				{
					state_EXECUTING_ATK();
					m_actionsManager->UpdateTargetsInRange();
				}
			}
			else if (t == 2)
				state_CHOSING_UNIT();
		}
		else if (m_gameplayState = EXECUTING_ATK)
		{
			if (!m_actionsManager->PerformAttack())
			{
				state_CHOSING_ACTION();
			}
		}
		/*
		switch (m_gameplayState)
		{
		case CHOSING_UNIT:
			if (!m_playerManagers[m_currentActivePlayer]->CheckUnitActions()) break;

			state_CHOSING_ACTION();
			break;
		case EXECUTING_ATK:
			if (!m_actionsManager->PerformAttack())
			{
				state_CHOSING_ACTION();
			}
		case CHOSING_ACTION:
			int t = m_actionsManager->ActionChosen();
			if (t == 0)
				state_EXECUTING_MOVE();
			else if (t == 1)
			{
				if (m_actionsManager->CheckTargetsInRange())
				{
					state_EXECUTING_ATK();
					m_actionsManager->UpdateTargetsInRange();
				}
			}
			else if (t == 2)
				state_CHOSING_UNIT();
			break;
	
		}*/
	}

	if (inputManager->GetPress(InputManager::KEY_ESCAPE))
	{
		
		return QUIT;
	}

	return CONTINUE;
}

void StrategyLevel::state_CHOSING_UNIT()
{
	m_gameplayState = CHOSING_UNIT;
	std::cout << "Chose a unit using the [A] & [D] keys" << std::endl << std::endl;
}
void StrategyLevel::state_CHOSING_ACTION()
{
	m_gameplayState = CHOSING_ACTION;
	std::cout << "Chose an action (top left) using the [W] & [S] keys" << std::endl << std::endl;
}
void StrategyLevel::state_EXECUTING_MOVE()
{
	m_gameplayState = EXECUTING_MOVE;
	std::cout << "Move the unit using the [W], [A], [S] & [D] keys" << std::endl << std::endl;
}
void StrategyLevel::state_EXECUTING_ATK()
{
	m_gameplayState = EXECUTING_ATK;
	std::cout << "Chose target using the [A] & [D] keys" << std::endl;
	std::cout << "[Enter] to perform attack" << std::endl << std::endl;
}
