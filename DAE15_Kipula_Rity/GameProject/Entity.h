#pragma once
#include "pch.h"
#include "utils.h"
#include "Component.h"
#include "Animation.h"
#include "Power.h"
#include <iostream>
#include <map>
#include <vector>

enum class EntityState {
	None,
	Idle,
	Run,
	Jump,
	FallingDown,
	Freefall,
	Flying,
	Landed,
	Sucking,
	BigIdle,
	BigRun,
	BigJump,
	BigLanded,
	BigFreefall,
};

class EntityManager;
class AnimationController;
class Animation;
class Entity : public Component {
public:
	explicit Entity(
		EntityManager* entityManager,
		const Vector2f& origin,
		const std::string& entityName
	);
	Entity& operator=(const Entity& rhs) = delete;
	Entity(const Entity& other) = delete;
	virtual ~Entity();

	virtual void Update(float elapsedSec);
	virtual void Draw() const;

	void MoveTo(float elapsedSec, const Vector2f& direction, float speed);
	bool TakeDamage(const int damage);

	virtual void OnStateChanged(); 
	virtual void OnDamage();
	virtual void OnDied();

	// SET METHODS
	void SetHealth(const int newHealth);
	void SetState(EntityState newState);
	void SetInvincible(bool status) { m_Invincible = status; }
	void SetAnimationData(const std::map<int, AnimationData>& entityAnimations) { m_AnimationsData = entityAnimations; };
	// GET METHODS
	AnimationController* GetAnimator() const { return m_pAnimator; };
	Power GetPower() const { return m_Power; };
	int GetHealth() const { return m_Health; };

	// STATE METHODS
	bool CanDamage() const;
	bool IsAlive() const { return (m_Health > 0); };
	bool IsInvincible() const { return m_Invincible; };
	
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

	// variables
	Power m_Power;
	bool m_Invincible;
	int m_Health;
	float m_TimeElapsedLastHit;
};


