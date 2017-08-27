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
			getline(infile, line); 
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

	std::cout << "Use [W] & [D] to make selection" << std::endl;
	std::cout << "Press [Enter] to chose" << std::endl;

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
		case QUIT_THIS:
			return GAME_STATE_CHANGE::QUIT;
		}		
	}
	
	return CONTINUE;
}


void MainMenu::ChangeArrowPosTo(int index)
{
	m_selectionArrow->SetPos(m_arrowPosX, m_arrowPosY[index]);
}