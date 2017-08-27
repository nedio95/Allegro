#include "Scene.h"

Scene::Scene()
{
	//m_manager = manager;
	m_Display = DisplayManager::GetDisplay();
}
Scene::~Scene()
{
	CleanObjects();
}

int Scene::UpdateLogic(InputManager* inputManager)
{
	return 0;
}

void Scene::RenderScene()
{
	if (GameObject::GetHead() == NULL) return;

	GameObject* drawObject = GameObject::GetHead();

	drawObject->Render(m_Display->GetPosX(),m_Display->GetPosY());

	while (drawObject->GetNext() != NULL)
	{
		drawObject = drawObject->GetNext();
		drawObject->Render( m_Display->GetPosX(), m_Display->GetPosY() );

	}
}

void Scene::CleanObjects()
{
	GameObject::CleanObjectList();
	for (unsigned i = 0; i < m_gameObjects.size(); i++)
	{
		delete m_gameObjects[i];
	}
}