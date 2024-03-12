#pragma once
#include <utils.h>
#include "Component.h"
#include <iostream>

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
	~Entity();
	virtual void Update(float elapsedSec);
	// GET METHODS
	AnimationController* GetAnimator() const { return m_pAnimator; };
	std::string GetEntityName() const { return m_Name; };
	Rectf GetEntityBounds() const { return m_BoundingBox; }
protected:
	AnimationController* m_pAnimator;
	EntityManager* m_pManager;
	Vector2f m_Position;
	Rectf m_BoundingBox;
	int m_Health;
};


