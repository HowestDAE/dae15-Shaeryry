#pragma once
#include "pch.h"
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
	void SetEnemyVisibleState(bool newState) { m_IsVisible = newState; };
	bool IsEnemyVisible() const { return m_IsVisible; };
protected:
	Vector2f GetDirectionVector(Entity* entity1,Entity* entity2);
private:
	bool m_IsVisible;
};

