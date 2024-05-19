#pragma once
#include "pch.h"
#include "Enemy.h"

class WaddleDee final : public Enemy
{
public:
	explicit WaddleDee(
		EntityManager* entityManager,
		const Vector2f& origin
	);
private:
};

