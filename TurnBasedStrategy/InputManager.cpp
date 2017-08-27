#include "InputManager.h"

InputManager::InputManager()
{
	for (int i = 0; i < SIZE_OF_KEYS_PRESSED_ENUM; i++)
	{
		key_hold[i] = false;
		key_down[i] = false;
	}
}

InputManager::~InputManager()
{

}

void InputManager::UpdateInput()
{
	for (int indexOfKey = 0; indexOfKey < SIZE_OF_KEYS_PRESSED_ENUM; indexOfKey++)
	{
		if (key_hold[indexOfKey] && key_down[indexOfKey])
			
			key_down[indexOfKey] = false;
	}
}

void InputManager::OnKeyDown(int indexOfKey)
{
	key_hold[indexOfKey] = true;
	key_down[indexOfKey] = true;
	
	/*
	if (keys_pressed)
	keys_pressed[indexOfKey] = true;
	else
	*/
	
	/*
	if (key_is_held[indexOfKey])
	{
		keys_pressed[indexOfKey] = false;
		std::cout << "Held " << indexOfKey << std::endl;
	}
	else
	{
		keys_pressed[indexOfKey] = true;
		key_is_held[indexOfKey] = true;
		std::cout << "Pressed " << indexOfKey << std::endl;
	}
	*/
	
}

void InputManager::OnKeyUp(int indexOfKey)
{
	key_hold[indexOfKey] = false;
	//std::cout << "Up " << indexOfKey << std::endl;
}

bool InputManager::GetPress(int indexOfKey)
{
	return key_down[indexOfKey];
	/*
	if (keys_pressed[indexOfKey] && key_first_press[indexOfKey])
	return true;
	return false;
	*/
}

bool InputManager::GetHold(int indexOfKey)
{
	return key_hold[indexOfKey];
}