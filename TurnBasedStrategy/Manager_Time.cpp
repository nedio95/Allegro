#include "Manager_Time.h"

TimeManager* TimeManager::s_Time = NULL;

TimeManager::TimeManager()
{
	m_deltaTime = 0;
	m_lastTime = al_get_time();
}

TimeManager::~TimeManager()
{

}

TimeManager* TimeManager::CreateTime()
{
	if (s_Time == NULL)
	{
		s_Time = new TimeManager();
	}
	else
	{
		std::cout << "ERROR: Time already exists" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		exit(1);
	}
	return s_Time;
}

void TimeManager::UpdateDeltaTime()
{
	float currentTime = al_get_time();
	s_Time->m_deltaTime = currentTime - s_Time->m_lastTime;
	s_Time->m_lastTime = currentTime;
}

float TimeManager::GetDT()
{
	return s_Time->m_deltaTime;
}