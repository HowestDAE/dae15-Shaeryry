#pragma once
#include "pch.h"
#include "Enemy.h"

class BrontoBurt final : public Enemy
{
public:
	explicit BrontoBurt(
		EntityManager* entityManager,
		const Vector2f& origin
	);

	virtual void Update(float elapsedSec) override;
	virtual void GoToTarget(float elapsedSec, Entity* target) override;
private:
};

