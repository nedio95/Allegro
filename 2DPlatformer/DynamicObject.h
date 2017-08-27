#pragma once

#include "GameObject.h"

class DynamicObject : public GameObject
{

public:
	DynamicObject(float posX, float posY)/* : GameObject(posX, posY)*/;
	~DynamicObject();

	virtual void UpdateLogic()override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();



protected:

	bool GravAffected; // 0 = No Gravity on this object, 1 = Gravity affects this object 
	float GravAcc;
	float m_vertVel;

	virtual void ApplyGravity();

	void TranslateHorizontal(float diffX);
	void TranslateVert(float diffY);

	float m_speedVert;
	float m_speedHor;


};