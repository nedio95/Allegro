//==========================
//Known Bugs:
// 1. Per Pixel Collision // Logical error, positioning of overlap is wrong // FIXED (?)
// 2. Destroying Objects // A way to do in the update function, recycling object positions in list // e.g. Coin on collision // FIXED (?)
//==========================


#include "GameObject.h"

GameObject* GameObject::head_gameObject = NULL;
GameObject* GameObject::tail_gameObject = NULL;

GameObject::GameObject(){}

GameObject::GameObject(float posX, float posY)
{
	m_hasCollision = true;

	meterToPixel = 32;
	m_posX =posX;
	m_posY =posY;

	List_AddObject();
}

GameObject::~GameObject()
{
	for (unsigned i = 0; i < m_skin.size(); i++)
	{
		al_destroy_bitmap(m_skin[i]);
		m_skin[i] = nullptr;
	}
}

void GameObject::List_AddObject()
{
	if (head_gameObject == NULL)
	{
		head_gameObject = this;
		tail_gameObject = this;
	}
	else
	{
		previous_gameObject = tail_gameObject;
		tail_gameObject->next_gameObject = this;
		tail_gameObject = this;
	}
}

float GameObject::GetX()
{
	return m_posX;
}

float GameObject::GetY()
{
	return m_posY;
}

void GameObject::SetPos(float newX, float newY)
{
	m_posX = newX;
	m_posY = newY;
}

void GameObject::SetPosToObj(GameObject* obj)
{
	m_posX = obj->GetX();
	m_posY = obj->GetY();
}


void GameObject::ChangePos(float difX, float difY)
{
	m_posX += difX;
	m_posY += difY;
}

void GameObject::ChangeX(float difX)
{
	m_posX += difX;
}

void GameObject::ChangeY(float difY)
{
	m_posX += difY;
}

int GameObject::GetSizeX()
{
	return al_get_bitmap_width(m_skin[m_currentFrame]);
}

int GameObject::GetSizeY()
{
	return al_get_bitmap_height(m_skin[m_currentFrame]);
}

void GameObject::LoadSkinSet(std::string skinsDirectory)
{
	std::string wtf2 = "./" + skinsDirectory;
	const char * dirAsChar = wtf2.c_str(); //("./" + skinsDirectory).c_str();

	//std::cout << dirAsChar << std::endl;

//	std::cout << "loadSkin ran" << std::endl;
	DIR *pDIR;
	struct dirent *entry;
	if (pDIR = opendir(dirAsChar))
	{
		while (entry = readdir(pDIR))
		{
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
			{
				//	std::cout << entry->d_name << "\n";
				/*
				char* temp = entry->d_name;
				std::string ws(temp);
				*/
				std::string bitmapFileDir = skinsDirectory + '/' + entry->d_name;

				//std::cout << entry->d_name << std::endl;
				//std::cout << bitmapFileDir << std::endl;
				

				LoadSkin(bitmapFileDir );
				LoadSystemSkin(bitmapFileDir);
			}
				
				
		}
	}
}

void GameObject::LoadSkin(std::string bitmap)
{
	ALLEGRO_BITMAP* tempBit = al_load_bitmap(bitmap.c_str());
	m_skin.push_back(tempBit);
	//m_skin.push_back(tempBit);
	int index = m_skin.size() - 1;

	if (!m_skin[index])
	{
		std::cout << "Error:Creature skin not loaded." << std::endl;
		std::cout << "Press any key to exit." << std::endl;
		_getch();
		exit(1);
	}

	al_convert_mask_to_alpha(m_skin[index], al_map_rgb(255, 0, 255));
}

void GameObject::LoadSystemSkin(std::string bitmap)
{
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

	ALLEGRO_BITMAP* tempBit = al_load_bitmap(bitmap.c_str());
	m_systemSkin.push_back(tempBit);
	int index = m_systemSkin.size() - 1;

	al_convert_mask_to_alpha(m_systemSkin[index], al_map_rgb(255, 0, 255));

	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);


	if (!m_systemSkin[index])
	{
		std::cout << "Error:Creature system skin not loaded." << std::endl;
		std::cout << "Press any key to exit." << std::endl;
		_getch();
	}
}

/*
void GameObject::LoadSkin(std::string bitmap)
{
	ALLEGRO_BITMAP* tempBit = al_load_bitmap(bitmap.c_str());
	m_skin.push_back(tempBit);
	m_skin.push_back(tempBit);
	int index = m_skin.size() - 1;

	if (!m_skin[index])
	{
		std::cout << "Error:Creature skin not loaded." << std::endl;
		return;
	}

	al_convert_mask_to_alpha(m_skin[index], al_map_rgb(255, 0, 255));
}
*/

void GameObject::UpdateAllLogic()
{
	if (tail_gameObject == NULL) return;
	GameObject* toUpdate = tail_gameObject;
	GameObject* toUpdateNext;

	bool Continue = 1;
	do{
		toUpdateNext = toUpdate->previous_gameObject;
		toUpdate->UpdateLogic();
		//	toUpdate = toUpdate->m_previousCreature;


		if (toUpdateNext != NULL)
		{
			toUpdate = toUpdateNext;
		}
		else Continue = 0;



	} while (Continue);
}

void GameObject::UpdateLogic()
{
		
}

bool GameObject::Collision(int direction, bool perPixel)
{
	GameObject* checkWith = tail_gameObject;
	do{
		if ((checkWith != this) && checkWith->m_hasCollision)
		{
			int xCol = checkWith->GetX();
			int yCol = checkWith->GetY();

			int widthCol = checkWith->GetSizeX();
			int heightCol = checkWith->GetSizeY();

			int width = GetSizeX();
			int height = GetSizeY();

			if (
				((m_posX - 1 < xCol + widthCol) && (m_posX + width > xCol))
				&&
				((m_posY - 1 < yCol + heightCol) && (m_posY + height > yCol))
				)
			{

				//return 1;
				//	if (perPixel)
				//	{
				if (PixelPerfectCollision(checkWith))
				{
					//return 1;
					//	std::cout << "Collision with " << std::endl;
					/*
					if ((direction == LEFT) && (m_posX > xCol))
					return 1;
					else if ((direction == RIGHT) && (m_posX < xCol))
					return 1;
					*/

					switch (direction)
					{
					case NONE:
						return 1;
					case UP:
						if (m_posY > yCol)
							//std::cout << "UP" << std::endl;
						return 1;
					case DOWN:
						if (m_posY < yCol)
							//std::cout << "DOWN" << std::endl;
							return 1;
					case LEFT:
						if (m_posX > xCol)
							return 1;
					case RIGHT:
						if (m_posX < xCol)
							return 1;
					}

				}
			}
			//else
			//return 1;

			//}
		}


		if (checkWith->previous_gameObject != NULL)
		{
			//	checkWith->displayName();
			//	checkWith->displayPrev();
			checkWith = checkWith->previous_gameObject;
		}

	} while (checkWith->previous_gameObject != NULL);

	return 0;
}

bool GameObject::PixelPerfectCollision(GameObject* col)
{
	bool returnThis = 0;
	al_lock_bitmap(m_systemSkin[m_currentFrame], al_get_bitmap_format(m_systemSkin[m_currentFrame]), ALLEGRO_LOCK_READONLY);
	al_lock_bitmap(col->m_systemSkin[col->m_currentFrame], al_get_bitmap_format(col->m_systemSkin[col->m_currentFrame]), ALLEGRO_LOCK_READONLY);

	int checkXobj = 0;
	int checkXcol = 0;
	int checkYobj = 0;
	int checkYcol = 0;

	int difX = col->GetX() - GetX();
	int difY = col->GetY() - GetY();

	int difXabs = abs(difX);
	int difYabs = abs(difY);

	int overlapX = abs(GetSizeX() - difXabs);
	int overlapY = abs(GetSizeY() - difYabs);

	if (difX > 0)
	{
		checkXobj = difXabs;
		checkXcol = 0; // overlapX;

	}
	else
	{
		checkXobj = 0; // overlapX;
		checkXcol = difXabs;
	}

	if (difY > 0)
	{
		checkYobj = difYabs;
		checkYcol = 0; // overlapY;

	}
	else
	{
		checkYobj = 0; // overlapY;
		checkYcol = difYabs;
	}


	/* TEST START 
	ALLEGRO_COLOR objPix;
	ALLEGRO_COLOR colPix;

	for (int x = 0; x < overlapX; x++)
	{
		for (int y = 0; y < overlapY; y++)
		{
			//objPix = al_get_pixel(m_systemSkin[m_currentFrame], x, y);
			//objPix = al_get_pixel(col->m_systemSkin[col->m_currentFrame], x, y);
			objPix = al_get_pixel(m_systemSkin[m_currentFrame], x + checkXobj, y + checkYobj);
			colPix = al_get_pixel(col->m_systemSkin[col->m_currentFrame], x + checkXcol, y + checkYcol);
			if (objPix.a != 0 && objPix.a != 0)
			{
				std::cout << "1";
			}
			else
				std::cout << "0";
			
		}
		std::cout << std::endl;
	}
	
	/* TEST END */
	
	for (int x = 0; x < overlapX; x++)
	{
		for (int y = 0; y < overlapY; y++)
		{
			ALLEGRO_COLOR objPixel = al_get_pixel(m_systemSkin[m_currentFrame], x + checkXobj, y + checkYobj);
			ALLEGRO_COLOR colPixel = al_get_pixel(col->m_systemSkin[col->m_currentFrame], x + checkXcol, y + checkYcol);

			if ((objPixel.a > 0) && (colPixel.a >0))
			{
				returnThis = 1;
				break;
			}
		}

		if (returnThis) break;

	}

	al_unlock_bitmap(m_systemSkin[m_currentFrame]);
	al_unlock_bitmap(col->m_systemSkin[col->m_currentFrame]);

	//if ()
	return returnThis;
}

void GameObject::Render(int disX, int disY)
{
	al_draw_bitmap(m_skin[m_currentFrame], (int)(m_posX-disX /* meterToPixel*/), (int)(m_posY-disY /* meterToPixel*/), 0);
	if (m_currentFrame < m_skin.size() - 1)
		m_currentFrame++;
	else
		m_currentFrame = 0;
}

GameObject* GameObject::GetNext()
{
	return next_gameObject;
}

GameObject* GameObject::GetPrevious()
{
	return previous_gameObject;
}

GameObject* GameObject::GetHead()
{
	return head_gameObject;
}

void GameObject::CleanObjectList()
{
	head_gameObject = nullptr;
	tail_gameObject = nullptr;
}

void GameObject::RecycleObject()
{
	GameObject* tailPrev = tail_gameObject->GetPrevious();
	tailPrev->next_gameObject = NULL;

	this->previous_gameObject->next_gameObject = tail_gameObject;
	this->next_gameObject->previous_gameObject = tail_gameObject;

	tail_gameObject->previous_gameObject = this->previous_gameObject;
	tail_gameObject->next_gameObject = this->next_gameObject;

	tail_gameObject = tailPrev;
}