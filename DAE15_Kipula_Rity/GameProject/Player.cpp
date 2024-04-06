#include "pch.h"
#include "Player.h" 
#include "Entity.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Transform.h"
#include "CollisionBody.h"
#include <map>

Player::Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName)
	: 
		Entity(manager, origin, entityName),
		m_JumpClock{ 0 },
		m_Jumping{false},
		m_PressedSpace{false}
{ 
	this->GetTransform()->SetWidth(DEFAULT_ENTITY_WIDTH);
	this->GetTransform()->SetHeight(DEFAULT_ENTITY_HEIGHT); 

	std::map<int, AnimationData> playerTracks{};
	playerTracks[0] = AnimationData{ "None",1,2,true };
	playerTracks[1] = AnimationData{"Idle",1,2,true};
	playerTracks[2] = AnimationData{ "Run",4,DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[3] = AnimationData{ "Jump",1,DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[4] = AnimationData{ "FallingDown",5,(DEFAULT_ANIMATION_UPDATE * .75f),false,2 };
	playerTracks[5] = AnimationData{ "Freefall",1,DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[6] = AnimationData{ "Landed",1,DEFAULT_ANIMATION_UPDATE,false,2 };

	this->SetAnimationData(playerTracks);
}

void Player::OnKeyDownEvent(const SDL_KeyboardEvent& e)
{

	switch (e.keysym.sym)
	{
		case SDLK_SPACE:
			if (!m_PressedSpace) {
				m_PressedSpace = true;
				Jump();
			}
			break;
		default:
			break;
	}
}

void Player::OnKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
		case SDLK_SPACE:
			if (m_PressedSpace) {
				JumpEnd();
				m_PressedSpace = false;
			}
			break;
		default:
			break;
	}

}

void Player::Update(float elapsedSec) 
{ 
	Transform* playerTransform{ this->GetTransform() };
	const float currentLookDirection{ playerTransform->GetLookDirection() };
	const Vector2f alphaCurrentVelocity{ playerTransform->GetCurrentVelocity() };

	// Default Update

	Entity::Update(elapsedSec);

	// Keyboard

	this->UpdateKeyboard(elapsedSec);

	// Physics && Movement

	this->GetTransform()->ApplyPhysics(elapsedSec);

	// Update States

	const Vector2f currentVelocity{ playerTransform->GetCurrentVelocity() };
	EntityState currentState{ m_State };
	EntityState nextState{ m_State };

	// Jump
	if (m_Jumping) {
		m_JumpClock += elapsedSec;

		float jumpDampening{ 1 };
		if (m_JumpClock >= (KIRBY_JUMP_MAX_TIME * .12f)) {
			jumpDampening = .08f;
		}
		//std::cout << "Jump Dampening : " << jumpDampening << std::endl;

		if (m_JumpClock < (KIRBY_JUMP_MAX_TIME * .5f)) {
			playerTransform->AddVelocity(Vector2f{ 0,((KIRBY_JUMP_POWER * jumpDampening) * elapsedSec) });
		}

		if (m_JumpClock >= KIRBY_JUMP_MAX_TIME) {
			// THIS IS THE END OF A JUMP
			JumpEnd();
			m_JumpClock = KIRBY_JUMP_MAX_TIME;
		}
	}

	if (GetCollisionBody()->IsGrounded()) // Small Grounded logic
	{
		// Run & Idle
		if (abs(currentVelocity.x) > 0) { // Run
			nextState = EntityState::Run;
		} else {
			nextState = EntityState::Idle; // Default idle state !
		}

		// Landing
		if (InAir()) { // Checks if the current state is in the air when you're just grounded !
			nextState = EntityState::Landed;
		}
	}
	else // Small Air Logic
	{ 
		// Falling
		if (currentVelocity.y < 0) { // Checks if Y motion is negative, which means you're falling !
			nextState = EntityState::Freefall;
		}
		// Jumping
		if (m_Jumping) {
			nextState = EntityState::Jump;
		}
		
	}

	SetState(nextState);

	// State Actions 

	currentState = m_State; // Update the variable because it could've potentially changed !

	// Landing Event
	if (currentState == EntityState::Landed) {
		m_JumpClock = 0;
		m_Jumping = false;
	};
	
	// Side Slip on run thing Event

	if (currentState == EntityState::Run) {

		const bool switchedDirection{ currentLookDirection != playerTransform->GetLookDirection() };
		const bool fullyRunning{ playerTransform->GetAcceleration() >= 80 };
		if (fullyRunning && switchedDirection) {
			playerTransform->SetAcceleration(0);
			m_pAnimator->PlayAnimation("Tilt", 1, 1)->SetUpdateTime(KIRBY_FLIP_SIDE_TIME);
		}
	}

	// Wall stop !
	if (playerTransform->GetCurrentVelocity().x <= 0 && abs(alphaCurrentVelocity.x) > 0 && GetCollisionBody()->IsWallbound()) {
		if (playerTransform->GetAcceleration() >= 50) {
			//std::cout << "Wall oomf chan" << std::endl;
			playerTransform->SetAcceleration(0);
			m_pAnimator->PlayAnimation("Squish", 1, 1)->SetUpdateTime(KIRBY_SQUISH_TIME);
		}
	}
}

bool Player::InAir()
{
	return 
		m_State == EntityState::Jump
		or m_State == EntityState::FallingDown
		or m_State == EntityState::Freefall;
}

void Player::Jump()
{	
	if (!m_Jumping && !InAir()) {
		m_JumpClock = 0;
		m_Jumping = true;
		GetTransform()->SetVelocity(Vector2f{ GetTransform()->GetVelocity().x ,0 });
	}
}

void Player::JumpEnd()
{
	if (m_Jumping) {
		m_pAnimator->PlayAnimation("FallingDown", 5, 1)->SetUpdateTime((DEFAULT_ANIMATION_UPDATE * .75f));
		m_Jumping = false;
	}

}

void Player::UpdateKeyboard(float elapsedSec)
{
	Transform* playerTransform{ this->GetTransform() };
	const float accelSpeed{ KIRBY_ACCELERATION_SPEED * elapsedSec };
	const float currentAccelerationRatio{ (playerTransform->GetAcceleration() / 100) };
	const Vector2f currentPosition{ this->GetTransform()->GetPosition() };
	bool inputPressed{ false };

	Vector2f direction( 
		playerTransform->GetCurrentVelocity().x * currentAccelerationRatio,
		0
	);

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT]) {
		direction.x = 1;
		playerTransform->AddAcceleration(accelSpeed);
		//playerTransform->SetAcceleration(100);
		inputPressed = true;
	} else if (pStates[SDL_SCANCODE_LEFT]) {
		direction.x = -1;
		playerTransform->AddAcceleration(accelSpeed);
		//playerTransform->SetAcceleration(100);
		inputPressed = true;
	};
	 
	this->MoveTo(elapsedSec, direction.Normalized(), KIRBY_MOVEMENT_SPEED * currentAccelerationRatio);
}

