#pragma once
#include "Entity.h"

class Player final
	: public Entity
{
public:
	Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName);
	virtual void Update(float elapsedSec) override;
	virtual void OnStateChanged() override;
	
	//States
	bool InAir();
	// Actions
	void Jump(bool holding,float elapsedSec);
private:
	void UpdateKeyboard(float elapsedSec);

	const float MOVEMENT_SPEED{ 270 };
	const float ACCELERATION_SPEED{ 550 };
	const float JUMP_POWER{ 32.5 };
	const float JUMP_HOLD_TIME{ 0.125 };
	const float FLIP_SIDE_TIME{ .125 };
	float m_JumpClock;
};

