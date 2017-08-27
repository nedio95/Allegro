#include "UIObject.h"

UIObject::UIObject(float posX, float posY, char type) : StaticObject(posX, posY)
{
	std::string path = "assets/Buttons/";
	path += type;
	LoadSkinSet(path);
}

UIObject::~UIObject()
{
	/*
	for (unsigned i = 0; i < m_skin.size(); i++)
	{
		al_destroy_bitmap(m_skin[i]);
		m_skin[i] = nullptr;
	}
	*/
}

