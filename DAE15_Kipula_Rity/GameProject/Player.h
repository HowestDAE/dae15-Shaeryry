#pragma once
#include "Entity.h"

class Player final
	: public Entity
{
public:
	Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName);
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

	const float MOVEMENT_SPEED{ 270 };
	const float ACCELERATION_SPEED{ 550 };
	const float JUMP_POWER{ (1250 * 12) };
	const float JUMP_HOLD_TIME{ 0.35f };
	const float FLIP_SIDE_TIME{ .125f };
	const float SQUISH_TIME{ .08f };
	
	bool m_PressedSpace;
	bool m_Jumping;
	float m_JumpClock;
};

