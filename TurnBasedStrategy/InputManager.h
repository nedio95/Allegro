#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

#include <allegro5/allegro.h>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void UpdateInput();

	void OnKeyDown(int indexOfKey);
	void OnKeyUp(int indexOfKey);

	bool GetPress(int indexOfKey);
	bool GetHold(int indexOfKey);

	enum KEYS_PRESSED_LIST
	{
		KEY_ESCAPE, KEY_ENTER, KEY_R, KEY_W, KEY_A, KEY_S, KEY_D, KEY_Q, SIZE_OF_KEYS_PRESSED_ENUM
	};

	bool key_hold[SIZE_OF_KEYS_PRESSED_ENUM];

	bool key_down[SIZE_OF_KEYS_PRESSED_ENUM];
};