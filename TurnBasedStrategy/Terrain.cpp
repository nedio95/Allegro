
#include "Terrain.h"

Terrain* Terrain::head_Terrain = NULL;
Terrain* Terrain::tail_Terrain = NULL;

Terrain::Terrain(){}

Terrain::Terrain(float posX, float posY, int type)
{
	m_type = type;
	m_passable = true;
	m_cost = 1;
	m_posX = posX;
	m_posY = posY;

	std::string dir = "assets/Scenery/";
	dir += type;
	LoadSkinSet(dir);
}

Terrain::~Terrain()
{
	for (unsigned i = 0; i < m_skin.size(); i++)
	{
		al_destroy_bitmap(m_skin[i]);
		m_skin[i] = nullptr;
	}

}

void Terrain::Render()
{
	al_draw_bitmap(m_skin[m_currentFrame], (int)(m_posX), (int)(m_posY), 0);
	if (m_currentFrame < m_skin.size() - 1)
		m_currentFrame++;
	else
		m_currentFrame = 0;
}

void Terrain::List_AddObject()
{
	if (head_Terrain == NULL)
	{
		head_Terrain = this;
		tail_Terrain = this;
	}
	else
	{
		previous_Terrain = tail_Terrain;
		tail_Terrain->next_Terrain = this;
		tail_Terrain = this;
	}
}

Terrain* Terrain::GetNext()
{
	return next_Terrain;
}

Terrain* Terrain::GetPrevious()
{
	return previous_Terrain;
}

Terrain* Terrain::GetHead()
{
	return head_Terrain;
}

void Terrain::CleanObjectList()
{
	head_Terrain = nullptr;
	tail_Terrain = nullptr;
}

void Terrain::RecycleObject()
{
	Terrain* tailPrev = tail_Terrain->GetPrevious();
	tailPrev->next_Terrain = NULL;

	this->previous_Terrain->next_Terrain = tail_Terrain;
	this->next_Terrain->previous_Terrain = tail_Terrain;

	tail_Terrain->previous_Terrain = this->previous_Terrain;
	tail_Terrain->next_Terrain = this->next_Terrain;

	tail_Terrain = tailPrev;
}