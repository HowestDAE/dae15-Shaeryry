#pragma once
#include <utils.h>
#include "Component.h"
#include <iostream>

enum class EntityState {
	None,
	Idle,
	Run,
	Jump,
};

class EntityManager;
class AnimationController;
class Entity : public Component
{
public:
	Entity(
		EntityManager* manager,
		const Vector2f& origin = Vector2f{ 0,0 },
		const std::string& entityName = "Kirby"
	);
	virtual ~Entity();
	virtual void Draw() const;
	virtual void Update(float elapsedSec);
	// GET METHODS
	AnimationController* GetAnimator() const { return m_pAnimator; };
	Rectf GetEntityBounds() const { return m_BoundingBox; }
protected:
	AnimationController* m_pAnimator;
	EntityManager* m_pManager;
	Vector2f m_Position;
	Rectf m_BoundingBox;
	EntityState m_State;

	// STATES
	bool m_GravityAffected;
};


