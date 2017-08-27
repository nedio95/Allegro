#include "UIObject.h"

UIObject::UIObject(float posX, float posY, char type) : StaticObject(posX, posY)
{
	std::string path = "assets/Buttons/";
	path += type;
	LoadSkinSet(path);
}

UIObject::~UIObject()
{

}