#include "pch.h"
#include "Transform.h"


Transform::Transform(): 
	m_Position(0,0),
	m_Rotation{0}
{
}

void Transform::Update(float elapsedSec)
{
	Vector2f currentPosition{ this->GetPosition() };
	Vector2f newPosition{ (currentPosition - Vector2f{0,(9.81f*elapsedSec)}) };

	//temporary check for ground !
	if (newPosition.y < 0) {
		newPosition.y = 0;
	};

	SetPosition(newPosition);
}
