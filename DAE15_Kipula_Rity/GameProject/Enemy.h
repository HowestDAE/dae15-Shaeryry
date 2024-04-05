#pragma once
#include "Entity.h"

enum class EnemyType {
	WaddleDoo,
};

class Enemy : public Entity
{
public:
	Enemy(
		EntityManager* entityManager,
		const Vector2f& origin,
		const std::string& entityName
	);

	virtual void Update(float elapsedSec) override;
	virtual void GoToTarget(float elapsedSec,Entity* target);
	virtual void AttackTarget(Entity* target);
private:
};

