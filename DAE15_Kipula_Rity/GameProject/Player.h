#pragma once
#include "pch.h"
#include "Entity.h"

class Player final : public Entity
{
public:
	explicit Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName);
	void OnKeyDownEvent(const SDL_KeyboardEvent& e);
	void OnKeyUpEvent(const SDL_KeyboardEvent& e);
	virtual void Update(float elapsedSec) override;
	
	//States
	bool CanControl() const;
	bool InAir();
	bool IsHitstunned() const;
	bool IsSucking() const { return m_Sucking; };
	bool IsDeflating() const;
	bool IsBig() const;
	// Actions
	void Jump();
	void JumpEnd();
	void SuckStart();
	void Suck();
	void SuckEnd();
	// Overriden stuff 
	virtual void OnDamage() override;
private:
	void UpdateKeyboard(float elapsedSec);

	bool m_PressedSpace;
	bool m_Jumping;
	bool m_Sucking;
	Entity* m_AbsorbedEntity;

	float m_DeflateClock;
	float m_JumpClock;
};

