#pragma once
#include "pch.h"
#include "Entity.h"

enum class EnemyType {
	WaddleDoo,
	WaddleDee,
	BrontoBurt
};

class Enemy : public Entity
{
public: 
	explicit Enemy(
		EntityManager* entityManager,
		const Vector2f& origin,
		const std::string& entityName
	);	

	virtual void Update(float elapsedSec) override;
	virtual void GoToTarget(float elapsedSec,Entity* target);
	virtual void AttackTarget(Entity* target);	
	virtual void SpecialAttack(Entity* target);

	void SetEnemyVisibleState(bool newState) { m_IsVisible = newState; };
	bool IsEnemyVisible() const { return m_IsVisible; }; 
	bool CanUseSpecial() const { return (m_SpecialClock > m_SpecialCooldown); }
	float GetClock() const { return m_Clock; };
protected:
	void SetTargetDirection(Entity* target);
	Vector2f GetDirectionVector(Entity* entity1,Entity* entity2);
	Vector2f m_TargetDirection;
	float m_SpecialCooldown;
	float m_Speed; 
	float m_SpecialClock;
	float m_Clock;
private:
	bool m_IsVisible;
	bool m_SavedDirection;
};

