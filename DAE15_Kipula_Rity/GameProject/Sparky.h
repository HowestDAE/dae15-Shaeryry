#pragma once
#include "pch.h"
#include "Enemy.h"

class Sparky final : public Enemy
{
public:
	explicit Sparky(
		EntityManager* entityManager,
		const Vector2f& origin
	);
	virtual void GoToTarget(float elapsedSec, Entity* target) override;
private:
	float m_JumpClock;
};

