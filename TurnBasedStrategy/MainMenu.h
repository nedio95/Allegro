#pragma once

#include "Scene.h"

class MainMenu : public Scene
{
public:
	MainMenu();
	~MainMenu();

	int UpdateLogic(InputManager* inputManager)override;

private:
	GameObject *m_selectionArrow;

	static enum ARROW_POS
	{
		START,
		QUIT,
		NUM_POS
	};
	
	float m_arrowPosX;
	float m_arrowPosY[ARROW_POS::NUM_POS];
	int m_arrowPosIndex;

	void ChangeArrowPosTo(int index);

	enum CHOICES
	{
		START_NEW,
		QUIT_THIS
	};
};