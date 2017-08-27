#include "Wall.h"

Wall::Wall(float posX, float posY) :StaticObject(posX, posY)
{
	LoadSkinSet("assets/Wall");
}

Wall::~Wall()
{

}


