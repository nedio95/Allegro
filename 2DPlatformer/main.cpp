//==========================
// Bugs Log
// 1. Level -> Scroll Screen // When the player is to right of the middle resets position weirdly
//
// FIXED (?)
// 2. GameObject -> Per Pixel Collision // ??? It worked before :( What did I do ??? // Logical error, positioning of overlap is wrong // FIXED (?)
// 3. Game Object // Destroying and managing list // FIXED (?) 
// 4. GameObject -> Dynamic Object -> Player // Collision checks is not suitable for jumping // FIXED
//==========================

#include "GameManager.h"

int main()
{
	GameManager *Manager = new GameManager();

	Manager->Game();

	return 0;
}
