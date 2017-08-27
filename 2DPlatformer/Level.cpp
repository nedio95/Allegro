//==========================
//Known Bugs:
// 1. Scroll Screen - When to the right of the middle
//==========================

#pragma once

#include "Level.h"

Level::Level(std::string levelNumber)
{
	m_LevelSizeX = 0;
	m_LevelSizeY = 0;

	m_blockSize = 32;

	m_HUDManager = HUDManager::CreateHUD();

	//m_Display = DisplayManager::GetDisplay();

	std::string levelToLoad = "Levels/Level" + levelNumber + ".txt";
	std::string line;
	std::ifstream infile(levelToLoad);

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
				if ((int)x > m_LevelSizeX)
				{
					m_LevelSizeX = x;
				}

				switch (line[x])
				{
				case GameObject::EMPTY:
					break;
				case GameObject::WALL:
					m_gameObjects.push_back(new Wall((float)x * 32, (float)y * 32));
					break;
				case GameObject::DOOR:
					m_gameObjects.push_back(new Door((float)x * 32, (float)y * 32));
					break;
				case GameObject::MONSTER_PATROL:
					m_gameObjects.push_back(new Monster_Patroling((float)x * 32, (float)y * 32));
					break;
				case GameObject::COIN:
					m_HUDManager->AddCoin();
					m_gameObjects.push_back(new Coin((float)x * 32, (float)y * 32));
					break;
				case GameObject::KEY:
					m_HUDManager->AddKey();
					m_gameObjects.push_back(new Key((float)x * 32, (float)y * 32));
					break;
				case GameObject::PLAYER:
					if (m_player != NULL)
					{
						std::cout << "ERROR: Duplication of player" << std::endl << "Press any key to exit";
						_getch();
					}
					Player* newPlayer = new Player((float)x * 32, (float)y * 32);
					m_gameObjects.push_back(newPlayer);
					m_player = newPlayer;

					break;
				
				}
				/*
				if (line[x] != '.')
				{
					m_gameObjects.push_back(new GameObject((float)x*32, (float)y*32));
				*/
			}
			y++;

		} while (!infile.eof()); // until the end of file (EOF) is reached

		infile.close(); // always close streams once finished

		m_LevelSizeX *= m_blockSize;
		m_LevelSizeY = y * m_blockSize;

	}
	else
	{
		std::cout << "Error opening file for input" << std::endl << "Press any key to exit";
		_getch();
		exit(1);
	}

	
}

Level::~Level()
{

}

int Level::UpdateLogic(InputManager* inputManager)
{
	int returnThis = ProcessInput(inputManager);

	if (GameObject::GetHead() != NULL)
	{
		GameObject::UpdateAllLogic();
	}

	ScrollScreen();

//	deltaTime = 0;

	return returnThis;
	
}

void Level::RenderScene()
{
	if (GameObject::GetHead() == NULL) return;

	GameObject* drawObject = GameObject::GetHead();

	drawObject->Render(m_Display->GetPosX(), m_Display->GetPosY());

	while (drawObject->GetNext() != NULL)
	{
		drawObject = drawObject->GetNext();
		drawObject->Render(m_Display->GetPosX(), m_Display->GetPosY());

	}

	m_HUDManager->RenderHUD();

}

int Level::ProcessInput(InputManager* inputManager)
{
	if (inputManager->GetPress(InputManager::KEY_W))
	{
		//std::cout << "W registered" << std::endl;
		m_player->Jump();
	}

	if (inputManager->GetPress(InputManager::KEY_S))
	{
	//	std::cout << "S registered" << std::endl;
	}

	if (inputManager->GetHold(InputManager::KEY_A))
	{
		m_player->MoveLeft();
		//std::cout << "A registered " << m_player->GetX() << std::endl;
	}

	if (inputManager->GetHold(InputManager::KEY_D)) // Why do I need "D" ???
	{
		m_player->MoveRight();
	//	std::cout << "D registered " << m_player->GetX() << std::endl;
	}

	if (inputManager->GetPress(InputManager::KEY_ESCAPE))
	{
	//	std::cout << "Esc registered" << std::endl;
		return QUIT;
	}

	return CONTINUE;
}

void Level::ScrollScreen()
{
	int disX = m_Display->GetPosX();
	int disSizeX = m_Display->GetSizeX();
	int plaX = m_player->GetX();

	if (plaX + m_player->GetSizeX() / 2 != disX + disSizeX / 2)
	{
		//m_Display->SetX( m_player->GetX() - disSizeX / 2);
		disX = plaX - disSizeX / 2;

		//	int arenaSizeX = disSizeX * m_blockSize;

		if (disX < 0)
			//m_Display->SetX(0);
			disX = 0;
		else if (m_Display->GetPosX() > /*arenaSizeX */ m_LevelSizeX - disSizeX)
			//m_Display->SetX(m_LevelSizeX - disSizeX);
			disX = m_LevelSizeX - disSizeX;

		m_Display->SetX(disX);
	}

	int disY = m_Display->GetPosY();
	int disSizeY = m_Display->GetSizeY();
	int plaY = m_player->GetY();

	if (plaY + m_player->GetSizeY() / 2 != disY + disSizeY / 2)
	{
		disY = plaY - disSizeY / 2;

		//int arenaSizeY = derArena->getSizeY() * derArena->getBlockSize();

		if (disY < 0)
			disY = 0;
		else if (disY > m_LevelSizeY - disSizeY)
			disY = m_LevelSizeY - disSizeY;

		m_Display->SetY(disY);
	}
}

//void Level::RenderLevel()
//{
//	if (GameObject::GetHead() == NULL) return;
//
//	GameObject* drawObject = GameObject::GetHead();
//
//	drawObject->Render();
//
//	while (drawObject->GetNext() != NULL)
//	{
//		drawObject = drawObject->GetNext();
//		drawObject->Render();
//
//	}
//
//	/*
//	do
//	{
//	drawObject->Render();
//
//	if (drawObject->GetNext() != NULL)
//	{
//	//	checkWith->displayName();
//	//	checkWith->displayPrev();
//	drawObject = drawObject->GetNext();
//	}
//
//	} while (drawObject->GetNext() != NULL);
//	*/
//
//	/*
//	for (unsigned row = 0; row < m_grid.size(); row++)
//	{
//	for (unsigned col = 0; col < m_grid[row].size(); row++)
//	{
//
//	}
//
//	}
//	*/
//}