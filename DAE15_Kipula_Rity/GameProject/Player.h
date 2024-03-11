#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	using Entity::Entity;
	virtual void Update(float elapsedSec) override;
private:
};

