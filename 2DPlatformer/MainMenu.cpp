#include "MainMenu.h"

MainMenu::MainMenu() : Scene()
{
	std::string menuToLoad = "Levels/MainMenu.txt";
	std::string line;
	std::ifstream infile(menuToLoad);

	if (infile.is_open()) // if file has correctly opened
	{
		int y = 0;
		int buttonCount = 0;
		do
		{
			getline(infile, line); // extract one line of file into string
			//std::cout << line << std::endl;  // and display it
			//arenaToFill->LoadArenaRow(line);
			//m_grid.push_back(line);
			for (unsigned x = 0; x < line.size(); x++)
			{
				if (line[x] != UIObject::EMPTY)
				{
					//UIObject obj = 
					m_gameObjects.push_back(new UIObject((float)x * 32, (float)y * 32, line[x]));
					if (line[x] == UIObject::ARROW)
					{
						m_selectionArrow = m_gameObjects[m_gameObjects.size()-1];
						m_arrowPosX = m_selectionArrow->GetX();
						//m_SelectionArrow->ChangePos(1, 1);
					}
					else
					{
						m_arrowPosY[buttonCount] = m_gameObjects[m_gameObjects.size() - 1]->GetY();
						buttonCount += 1;
					}
				}
				/*
				switch (line[x])
				{
				case UIObject::EMPTY:
					break;
				
				case UIObject::START:
					m_gameObjects.push_back(new UIObject((float)x * 32, (float)y * 32));
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
	}
	else
	{
		std::cout << "Error opening file for input" << std::endl;
		exit(1);
	}

	std::cout << "Press Enter to start" << std::endl;
	std::cout << "Don't try to select anythign else" << std::endl;
}

MainMenu::~MainMenu()
{
	delete m_selectionArrow;
}

int MainMenu::UpdateLogic(InputManager* inputManager)
{
	if (inputManager->GetPress(InputManager::KEY_W))
	{
	//	std::cout << "W registered" << std::endl;
		m_arrowPosIndex -= 1;
		if (m_arrowPosIndex < 0)
		{
			m_arrowPosIndex = NUM_POS - 1;
			
		}
		ChangeArrowPosTo(m_arrowPosIndex);
		
 	}

	if (inputManager->GetPress(InputManager::KEY_S))
	{
		m_arrowPosIndex += 1;
		if (m_arrowPosIndex >= NUM_POS)
		{
			m_arrowPosIndex = 0;
		}
		ChangeArrowPosTo(m_arrowPosIndex);
	}

	if (inputManager->GetPress(InputManager::KEY_ENTER))
	{
		switch (m_arrowPosIndex)
		{
		case START_NEW:
				return NEW_GAME;
		case START_SAVED:
				return LOAD;
		case QUIT_THIS:
			return QUIT;
		}

		
			
	}
	
	return CONTINUE;
}


void MainMenu::ChangeArrowPosTo(int index)
{
	m_selectionArrow->ChangePos(m_arrowPosX, m_arrowPosY[index]);
}