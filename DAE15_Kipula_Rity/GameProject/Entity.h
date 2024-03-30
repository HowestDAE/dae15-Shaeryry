#pragma once
#include <utils.h>
#include "Component.h"
#include <iostream>
#include <map>
#include <vector>
#include "Animation.h"


enum class EntityState {
	None,
	Idle,
	Run,
	Jump,
	FallingDown,
	Freefall,
	Landed,
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

	void MoveTo(float elapsedSec, const Vector2f& direction, float speed);
	virtual void OnStateChanged();

	void SetState(EntityState newState);
	void SetAnimationData(const std::map<int, AnimationData>& entityAnimations) { m_AnimationsData = entityAnimations; };

	// GET METHODS
	AnimationController* GetAnimator() const { return m_pAnimator; };
	
protected:
	// manager
	EntityManager* m_pManager;

	// states
	
	bool m_InAir;
	EntityState m_State;
	EntityState m_OldState;

	// animations
	Animation* m_pCoreAnimation;
	AnimationController* m_pAnimator;
	std::map<int, AnimationData> m_AnimationsData;
};


