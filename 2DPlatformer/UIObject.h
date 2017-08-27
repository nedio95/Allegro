#include "StaticObject.h"

class UIObject : public StaticObject
{
public:
	UIObject(float posX, float posY, char type);
	~UIObject();

	static enum UIOBJ_TYPE
	{
		EMPTY = '.',
		START = 'S',
		QUIT = 'Q',
		ARROW = 'P'
	};
};

