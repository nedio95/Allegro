//==========================
//Known Bugs:
// 1. Per Pixel Collision // Logical error, positioning of overlap is wrong // FIXED (?)
// 2. Destroying Objects // A way to do in the update function, recycling object positions in list // e.g. Coin on collision // FIXED (?)
//==========================


#include "Unit.h"

Unit* Unit::head_Unit = NULL;
Unit* Unit::tail_Unit = NULL;

Unit::Unit(){}

Unit::Unit(int posX, int posY)
{
	m_posX = posX;
	m_posY = posY;
	m_isAlive = true;

	m_skinDead = al_load_bitmap("./assets/Dead/DeadUnitRedX.bmp");
	al_convert_mask_to_alpha(m_skinDead, al_map_rgb(255, 0, 255));

	List_AddObject();
}

Unit::~Unit()
{
	for (unsigned i = 0; i < m_skin.size(); i++)
	{
		al_destroy_bitmap(m_skin[i]);
		m_skin[i] = nullptr;
	}

}

void Unit::List_AddObject()
{
	if (head_Unit == NULL)
	{
		head_Unit = this;
		tail_Unit = this;
	}
	else
	{
		previous_Unit = tail_Unit;
		tail_Unit->next_Unit = this;
		tail_Unit = this;
	}
}

bool Unit::IsAlive()
{
	return m_isAlive;
}

int Unit::GetX()
{
	return m_posX;
}

int Unit::GetY()
{
	return m_posY;
}

void Unit::SetPos(int newX, int newY)
{
	m_posX = newX;
	m_posY = newY;
}

void Unit::ChangePos(int difX, int difY)
{
	m_posX += difX;
	m_posY += difY;
}

void Unit::ChangeX(int difX)
{
	m_posX += difX;
}

void Unit::ChangeY(int difY)
{
	m_posX += difY;
}

int Unit::GetSizeX()
{
	return al_get_bitmap_width(m_skin[m_currentFrame]);
}

int Unit::GetSizeY()
{
	return al_get_bitmap_height(m_skin[m_currentFrame]);
}

int Unit::GetAtkPt()
{
	return m_atkPoints;
}

int Unit::GetAtkPtMax()
{
	return m_maxAtkPoints;
}

int Unit::GetMovePt()
{
	return m_movePoints;
}

void Unit::ResetPt()
{
	m_atkPoints = m_maxAtkPoints;
	m_movePoints = m_maxMovePoints;
}

void Unit::TakeDamage(int dmg)
{
	if (!m_isAlive) return;
	std::cout << "dmg" << std::endl;
	m_currentHealth -= dmg;
	if (m_currentHealth <= 0)
	{
		std::cout << "dead" << std::endl;
		m_atkPoints = 0;
		m_movePoints = 0;
		m_currentHealth = 0;
		m_isAlive = false;

		
		LoadSkinSet("assets/Monster");
		m_currentFrame = 0;
	}
}

int Unit::GetDamage()
{
	return m_atkPower;
}

void Unit::DeductPoint(bool whichpoint)
{
	if (whichpoint)
	{
		m_movePoints--;
		if (m_movePoints < 0)
			m_movePoints = 0;
	}
	else
	{
		m_atkPoints--;
		if (m_atkPoints < 0)
			m_atkPoints = 0;
	}
}
		

bool Unit::GetActionsAvailability()
{
	if (m_atkPoints == 0 && m_movePoints == 0) return false;
	return true;
}

void Unit::LoadSkinSet(std::string skinsDirectory)
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


				LoadSkin(bitmapFileDir);
			}


		}
	}
}

void Unit::LoadSkin(std::string bitmap)
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


void Unit::UpdateAllLogic()
{
	Unit* toUpdate = tail_Unit;
	Unit* toUpdateNext;

	bool Continue = 1;
	do{
		toUpdateNext = toUpdate->previous_Unit;
		toUpdate->UpdateLogic();
		//	toUpdate = toUpdate->m_previousCreature;


		if (toUpdateNext != NULL)
		{
			toUpdate = toUpdateNext;
		}
		else Continue = 0;



	} while (Continue);
}

void Unit::UpdateLogic()
{

}

void Unit::Render()
{
	al_draw_bitmap(m_skin[m_currentFrame], (int)(m_posX), (int)(m_posY), 0);
	if (m_currentFrame < m_skin.size() - 1)
		m_currentFrame++;
	else
		m_currentFrame = 0;

	if (!m_isAlive)
	{
		al_draw_bitmap(m_skinDead, (int)(m_posX), (int)(m_posY), 0);
	}

	HUDManager::RenderUnitHp(m_posX, m_posY, m_currentHealth);


}

Unit* Unit::GetNext()
{
	return next_Unit;
}

Unit* Unit::GetPrevious()
{
	return previous_Unit;
}

Unit* Unit::GetHead()
{
	return head_Unit;
}

void Unit::CleanObjectList()
{
	head_Unit = nullptr;
	tail_Unit = nullptr;
}

void Unit::RecycleObject()
{
	Unit* tailPrev = tail_Unit->GetPrevious();
	tailPrev->next_Unit = NULL;

	this->previous_Unit->next_Unit = tail_Unit;
	this->next_Unit->previous_Unit = tail_Unit;

	tail_Unit->previous_Unit = this->previous_Unit;
	tail_Unit->next_Unit = this->next_Unit;

	tail_Unit = tailPrev;
}