#include "Manager_Display.h"

DisplayManager* DisplayManager::s_Display = NULL;
ALLEGRO_DISPLAY* DisplayManager::m_display = NULL;

DisplayManager::DisplayManager()
{
	m_posX = 0;
	m_posY = 0;
	m_screenX = 240;
	m_screenY = 240;
	m_sizeX = 32 * 10;
	m_sizeY = 32 * 10;

	m_display = al_create_display(m_sizeX, m_sizeY); // create a display window by given sizes
	
	if (!m_display)
	{
		std::cout << "ERROR: Display initialisation failed" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		exit(1);
	}
	
	al_set_window_position(m_display, m_screenX, m_screenY); // position display window on screen
}

DisplayManager::~DisplayManager()
{

}

DisplayManager* DisplayManager::CreateDisplay()
{
	if (s_Display == NULL)
	{
		s_Display = new DisplayManager();
	}
	else
	{
		std::cout << "ERROR: Display already exists" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		exit(1);
	}
	return s_Display;
}

DisplayManager* DisplayManager::GetDisplay()
{
	return s_Display;
}

ALLEGRO_DISPLAY* DisplayManager::GetAlDisplay()
{
	return m_display;
}

float DisplayManager::GetPosX()
{
	return m_posX;
}

float DisplayManager::GetPosY()
{
	return m_posY;
}

void DisplayManager::SetX(float newX)
{
	m_posX = newX;
}

void DisplayManager::SetY(float newY)
{
	m_posY = newY;
}

int DisplayManager::GetSizeX()
{
	return m_sizeX;
}

int DisplayManager::GetSizeY()
{
	return m_sizeY;
}