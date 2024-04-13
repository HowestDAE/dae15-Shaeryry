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
	bool InAir();
	// Actions
	void Jump();
	void JumpEnd();
private:
	void UpdateKeyboard(float elapsedSec);
	bool m_PressedSpace;
	bool m_Jumping;
	float m_JumpClock;
};

