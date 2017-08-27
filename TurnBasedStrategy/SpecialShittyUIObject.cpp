#include "SpecialShittyUIObject.h"

SpecObj::SpecObj(float posX, float posY, char type)
{
	m_posX = posX;
	m_posY = posY;
	m_currentFrame = 0;
	
	std::string path = "assets/Buttons/";
	path += type;
	LoadSkinSet(path);
}

SpecObj::~SpecObj()
{
	for (unsigned i = 0; i < m_skin.size(); i++)
	{
	al_destroy_bitmap(m_skin[i]);
	m_skin[i] = nullptr;
	}
}

void SpecObj::SetPos(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void SpecObj::LoadSkinSet(std::string skinsDirectory)
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

void SpecObj::LoadSkin(std::string bitmap)
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

void SpecObj::Render()
{
	al_draw_bitmap(m_skin[m_currentFrame], (int)(m_posX), (int)(m_posY), 0);
	if (m_currentFrame < m_skin.size() - 1)
		m_currentFrame++;
	else
		m_currentFrame = 0;
}