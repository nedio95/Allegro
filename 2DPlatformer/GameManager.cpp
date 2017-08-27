#include "GameManager.h"


GameManager::GameManager()
{
	
	m_framesPerSecond = 60;

	//deltaTime = 0;
	//lastTime = al_get_time();

	testBool = 1;
	testInt = 100;

	if (!InitialiseAllegro())
	{
		std::cout << "ERROR: Allegro initialization failed" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		exit(1);
	};

	m_inputManager = new InputManager();
	m_timeManager = TimeManager::CreateTime();
	
}

GameManager::~GameManager()
{

}

void GameManager::Game()
{
	

	//CurrentMainMenu 
	CurrentMenu = new MainMenu();
	CurrentScene = CurrentMenu;

	while (true)
	{
		m_inputManager->UpdateInput();
		GameLoop();
	}
}


bool GameManager::InitialiseAllegro()
{
	if (!al_init())
	{
		std::cout << "Allegro initialisation failed" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		return 0;
	}

	display = DisplayManager::CreateDisplay();

	// tell allegro program needs keyboard input
	if (!al_install_keyboard())
	{
		std::cout << "Keyboard initialisation failed" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		return 0;
	}

	timer = al_create_timer(1.0 / m_framesPerSecond);

	if (!timer)
	{
		std::cout << "Timer initialisation failed" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		return 0;
	}

	// need to create an event queue so allegro can respond to events, such as keypresses
	event_queue = al_create_event_queue();

	if (!event_queue)
	{
		std::cout << "Event queue creation failed" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		al_destroy_display(DisplayManager::GetAlDisplay());
		return 0;
	}

	// register  display with the event queue, so display change events can be processed
	al_register_event_source(event_queue, al_get_display_event_source(DisplayManager::GetAlDisplay()));

	// register keyboard with the event queue, so keypress events can be processed
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	timer_event_queue = al_create_event_queue();

	if (!timer_event_queue)
	{
		std::cout << "Event queue creation failed" << std::endl;
		std::cout << "Press any key to exit" << std::endl;
		_getch();
		al_destroy_display(DisplayManager::GetAlDisplay());
		return 0;
	}

	al_register_event_source(timer_event_queue, al_get_timer_event_source(timer));

	//Bitmaps

	al_init_image_addon();

	//Font

	al_init_font_addon();
	al_init_ttf_addon();

	al_init_primitives_addon();

	return 1;
}

void GameManager::GameLoop()
{
	/*
	if (testBool)
	{
		testBool = 0;
		std::cout << lastTime << std::endl;
	}
	*/
	TimeManager::UpdateDeltaTime();

	/*
	if (testInt > 0)
	{
		testInt-= 1;
		std::cout << deltaTime << std::endl;
	}
	*/
	ProcessEvents();

	LogicUpdate();

	RenderUpdate();

}

void GameManager::ProcessEvents()
{
	ALLEGRO_EVENT allegro_event;

	while (al_get_next_event(event_queue, &allegro_event))
	{

		if (allegro_event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (allegro_event.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				m_inputManager->OnKeyDown(m_inputManager->KEY_ESCAPE);
				break;
			case ALLEGRO_KEY_ENTER:
				m_inputManager->OnKeyDown(m_inputManager->KEY_ENTER);
				break;
			case ALLEGRO_KEY_R:
				m_inputManager->OnKeyDown(m_inputManager->KEY_R);
				break;
			case ALLEGRO_KEY_W:
				m_inputManager->OnKeyDown(m_inputManager->KEY_W);
				break;
			case ALLEGRO_KEY_A:
				m_inputManager->OnKeyDown(m_inputManager->KEY_A);
				break;
			case ALLEGRO_KEY_S:
				m_inputManager->OnKeyDown(m_inputManager->KEY_S);
				break;
			case ALLEGRO_KEY_D:
				m_inputManager->OnKeyDown(m_inputManager->KEY_D);
				break;
			}

		}
		else if (allegro_event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (allegro_event.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				m_inputManager->OnKeyUp(m_inputManager->KEY_ESCAPE);
				break;
			case ALLEGRO_KEY_ENTER:
				m_inputManager->OnKeyUp(m_inputManager->KEY_ENTER);
				break;
			case ALLEGRO_KEY_R:
				m_inputManager->OnKeyUp(m_inputManager->KEY_R);
				break;
			case ALLEGRO_KEY_W:
				m_inputManager->OnKeyUp(m_inputManager->KEY_W);
				break;
			case ALLEGRO_KEY_A:
				m_inputManager->OnKeyUp(m_inputManager->KEY_A);
				break;
			case ALLEGRO_KEY_S:
				m_inputManager->OnKeyUp(m_inputManager->KEY_S);
				break;
			case ALLEGRO_KEY_D:
				m_inputManager->OnKeyUp(m_inputManager->KEY_D);
				break;
			}
		}

		if (updateState == UPDATE_STATE_LOGIC)
		{
			al_flush_event_queue(timer_event_queue);

			updateState = UPDATE_STATE_RENDER;
		}
		/*
		else
		{
			consecutiveLogicUpdates = 0;

			while (al_get_next_event(timer_event_queue, &allegro_event))
			{
				consecutiveLogicUpdates++;

				gamestate = GAME_STATE_LOGIC;
			}
		}
		*/
	}
}

void GameManager::LogicUpdate()
{
	/*
	switch (CurrentGameState)
	{
		case
	}
	*/
	int nextState = CurrentScene->UpdateLogic(m_inputManager);

	if (nextState != Scene::CONTINUE) CurrentGameState = nextState;

	switch (nextState)
	{
	case Scene::CONTINUE:
		return;
	case Scene::MAIN_MENU:
		delete CurrentScene;
		std::cout << "MainMenu" << std::endl;
		CurrentScene = new MainMenu();
		return;
	case Scene::NEW_GAME:
		delete CurrentScene;
		CurrentScene = nullptr;
		std::cout << "New Game" << std::endl;
		CurrentScene = new Level("1");
		return;
	case Scene::LOAD:
		return;
	case Scene::QUIT:
		exit(1);
		return;
	case Scene::PAUSE:
		return;
	}
		
}

void GameManager::RenderUpdate()
{
	al_clear_to_color(al_map_rgb(150, 150, 150));

	CurrentScene->RenderScene();

	al_flip_display();

	/*
	ALLEGRO_BITMAP* someBit = al_load_bitmap("assets/Wall.bmp");
	al_draw_bitmap(someBit, 0, 0, 0);
	*/
}

void GameManager::LoadLevel(std::string levelNumber)
{
	delete CurrentScene;
	CurrentScene = new Level(levelNumber);
}