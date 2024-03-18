#pragma once
#include <utils.h>
#include "Component.h"
#include <iostream>
#include <map>
#include <vector>
#include "Animation.h"


enum class EntityState {
	None,
	Idle = 1,
	Run = 2,
	Jump = 3,
};

class EntityManager;
class AnimationController;
class Animation;
class Entity : public Component
{
public:
	Entity(
		EntityManager* entityManager,
		const Vector2f& origin = Vector2f{ 0,0 },
		const std::string& entityName = "Kirby"
	);
	virtual ~Entity();
	virtual void Draw() const;
	virtual void Update(float elapsedSec);
	virtual void OnStateChanged();

	void SetState(EntityState newState);
	void SetAnimationData(const std::map<int, AnimationData>& entityAnimations) { m_AnimationsData = entityAnimations; };
	// GET METHODS
	AnimationController* GetAnimator() const { return m_pAnimator; };
	Rectf GetEntityBounds() const { return m_BoundingBox; };
	
protected:
	EntityManager* m_pManager;

	Animation* m_pCoreAnimation;
	AnimationController* m_pAnimator;

	Rectf m_BoundingBox;
	EntityState m_State;
	EntityState m_OldState;
	std::map<int, AnimationData> m_AnimationsData;
};


