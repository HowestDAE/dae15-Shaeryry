#pragma once
#include "pch.h"
#include "Enemy.h"

class HotHead final : public Enemy
{
public:
	explicit HotHead(
		EntityManager* entityManager,
		const Vector2f& origin
	);
private:
};

