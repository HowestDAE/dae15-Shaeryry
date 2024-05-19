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
	SharpLeftSlopeIdle,
	SoftLeftSlopeIdle,
	SoftRightSlopeIdle,
	SharpRightSlopeIdle,
	Run,
	Jump,
	FallingDown,
	Freefall,
	Flying,
	Sliding,
	Climbing,
	Landed,
	SharpLeftLanded,
	SoftLeftLanded,
	SoftRightLanded,
	SharpRightLanded,
	Sucking,
	BigIdle,
	BigRun,
	BigJump,
	BigLanded,
	BigFreefall,
	Crouched,
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
	void SetPower(const PowerTypes power);
	void SetVisible(bool newState) { m_Visible = newState; };
	void SetDeathDelay(float deathTime) { m_DeathDelay = deathTime; };

	// GET METHODS
	AnimationController* GetAnimator() const { return m_pAnimator; };
	Power* GetPower() const { return m_pPower; };
	int GetHealth() const { return m_Health; };
	EntityManager* GetManager() const { return m_pManager; };
	float GetHitClock() const { return m_TimeElapsedLastHit; };
	float GetDeathDelay() const { return m_DeathDelay; };
	// STATE METHODS
	bool CanDamage() const;
	bool IsAlive() const { return (m_Health > 0); };
	bool IsInvincible() const { return m_Invincible; };	
	bool HasDied() const { return m_Died; };
	bool IsVisible() const { return m_Visible; };
	bool CanRemove() const { return (m_DeathClock > m_DeathDelay); };
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

	Power* m_pPower;
	bool m_Died;
	bool m_Invincible;
	bool m_Visible;
	int m_Health;
	float m_TimeElapsedLastHit;
	float m_DeathClock;
	float m_DeathDelay;
};


