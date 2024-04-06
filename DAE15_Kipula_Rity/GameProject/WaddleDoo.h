#pragma once
#include "pch.h"
#include "Enemy.h"

class WaddleDoo : public Enemy
{
public:
	WaddleDoo(
		EntityManager* entityManager,
		const Vector2f& origin
	);
	virtual void GoToTarget(float elapsedSec, Entity* target) override;
private:
	bool m_SavedDirection;
	Vector2f m_WaddleDooTargetDirection;
};

