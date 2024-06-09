#pragma once
#include "pch.h"
#include "Entity.h"
#include "Power.h"
#include "ProjectileManager.h"

class Player final : public Entity
{
public:
	explicit Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(Player&& other) = delete;
	~Player();
	void OnKeyDownEvent(const SDL_KeyboardEvent& e);
	void OnKeyUpEvent(const SDL_KeyboardEvent& e);
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual void SetPower(const PowerTypes power) override;
	//States
	bool CanControl() const;
	bool HasPower() const;
	bool InAir() const;
	bool IsHitstunned() const;
	bool IsSucking() const { return m_Sucking; };
	bool IsDeflating() const;
	bool IsBig() const;
	bool IsFull() const { return m_Absorbed; };
	bool IsShooting() const;
	bool IsFlying() const;
	bool HasLeft() const { return (m_LeavingClock > KIRBY_LEAVE_TIME); };
	bool IsLeaving() const { return m_Leaving; };
	bool IsCrouched() const { return m_Crouched; };
	bool IsOnDoor() const;
	bool IsDeathPause() const { return (HasDied() and (m_DeathClock < KIRBY_DEATH_PAUSE_TIME)); };
	// Actions
	void Dying();
	void UsePower();
	void CrouchEnd();
	void OnCrouch();
	void ClampToScreen();
	void Jump();
	void JumpEnd();
	void SuckStart();
	void Suck();
	void SuckEnd();
	void Shoot();
	void Fly();
	void FlyEnd();
	void Leave();
	// Overriden stuff 
	virtual void OnDamage() override;
private:
	void UpdateKeyboard(float elapsedSec);

	PlayerData& m_PlayerData;
	ProjectileManager* m_Shooter;
	PowerTypes m_AbsoredPower;
	std::string m_nextWorld;
	
	// Variables
	float m_GroundDOTproduct;
	float m_LookVectorToGroundDOTproduct;

	// States

	bool m_CanUsePower;
	bool m_MoveInput;
	bool m_Crouched;
	bool m_CanCrouch;

	bool m_IsDying;
	bool m_Leaving;
	bool m_PressedSpace;
	bool m_Flying;
	bool m_Jumping;
	bool m_Sucking;
	bool m_Absorbed;
	bool m_CanShoot;
	bool m_SuckingTargets;

	bool m_SlidingDownSlope;
	bool m_GoingUpSlope;
	bool m_GoingUpSteepSlope;
		
	// Clocks

	float m_FlyingEndClock;
	float m_FlyingClock;
	float m_RunClock;
	float m_ShootingClock;
	float m_DeflateClock;
	float m_JumpClock;
	float m_LeavingClock;
	float m_AirDistance;
};

