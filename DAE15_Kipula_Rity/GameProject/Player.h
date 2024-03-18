#pragma once
#include "Entity.h"

class Player final
	: public Entity
{
public:
	Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName);
	virtual void Update(float elapsedSec) override;
private:
	void UpdateKeyboard(float elapsedSec);

	float m_MovementSpeed{200};
};

