#pragma once
#include "pch.h"
#include "Entity.h"
#include "Power.h"
#include "ProjectileManager.h"

class Player final : public Entity
{
public:
	explicit Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName);
	~Player();
	void OnKeyDownEvent(const SDL_KeyboardEvent& e);
	void OnKeyUpEvent(const SDL_KeyboardEvent& e);
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	
	//States
	bool CanControl() const;
	bool InAir();
	bool IsHitstunned() const;
	bool IsSucking() const { return m_Sucking; };
	bool IsDeflating() const;
	bool IsBig() const;
	bool IsFull() const { return m_Absorbed; };
	bool IsShooting() const;
	// Actions
	void Jump();
	void JumpEnd();
	void SuckStart();
	void Suck();
	void SuckEnd();
	void Shoot();
	// Overriden stuff 
	virtual void OnDamage() override;
private:
	void UpdateKeyboard(float elapsedSec);

	ProjectileManager* m_Shooter;
	Power m_AbsoredPower;
	
	bool m_PressedSpace;
	bool m_Jumping;
	bool m_Sucking;
	bool m_Absorbed;
	bool m_CanShoot;
	bool m_SuckingTargets;

	float m_RunClock;
	float m_ShootingClock;
	float m_DeflateClock;
	float m_JumpClock;
};

