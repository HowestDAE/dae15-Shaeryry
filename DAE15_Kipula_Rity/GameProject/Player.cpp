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
		m_JumpClock{ 0 }
{ 
	this->GetTransform()->SetWidth(40);
	this->GetTransform()->SetHeight(40);

	std::map<int, AnimationData> playerTracks{};
	playerTracks[0] = AnimationData{ "None",1,2,true };
	playerTracks[1] = AnimationData{"Idle",1,2,true};
	playerTracks[2] = AnimationData{ "Run",4,Animation::DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[3] = AnimationData{ "Jump",1,Animation::DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[4] = AnimationData{ "FallingDown",5,(Animation::DEFAULT_ANIMATION_UPDATE * .75f),false,2 };
	playerTracks[5] = AnimationData{ "Freefall",1,Animation::DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[6] = AnimationData{ "Landed",1,Animation::DEFAULT_ANIMATION_UPDATE,false,2 };

	this->SetAnimationData(playerTracks);
}

void Player::Update(float elapsedSec) 
{ 
	Transform* playerTransform{ this->GetTransform() };
	const float currentLookDirection{ playerTransform->GetLookDirection() };

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

	if (GetCollisionBody()->IsGrounded()) // Small Grounded logic
	{
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
		if (currentState == EntityState::Jump) {
			nextState = EntityState::FallingDown;
		};
	}

	SetState(nextState);

	// State Actions 

	currentState = m_State; // Update the variable because it could've potentially changed !

	// Landing Event
	if (currentState == EntityState::Landed) {
		m_JumpClock = 0;
	};
	
	// Side Slip on run thing Event

	if (currentState == EntityState::Run) {
		const bool switchedDirection{ currentLookDirection != playerTransform->GetLookDirection() };
		const bool fullyRunning{ playerTransform->GetAcceleration() >= 80 };
		if (fullyRunning && switchedDirection) {
			playerTransform->SetAcceleration(0);
			m_pAnimator->PlayAnimation("Tilt", 1, 1)->SetUpdateTime(FLIP_SIDE_TIME);
		}
	}
}

void Player::OnStateChanged()
{
	Entity::OnStateChanged();
	//std::cout << "Current state -> " << int(m_State) << std::endl;
}

bool Player::InAir()
{
	return 
		m_State == EntityState::Jump
		or m_State == EntityState::FallingDown
		or m_State == EntityState::Freefall;
}

void Player::Jump(bool holding,float elapsedSec)
{	
	bool IsJumping{ holding && (m_JumpClock <= JUMP_HOLD_TIME) };
	if (IsJumping) {
		SetState(EntityState::Jump);
		GetTransform()->AddVelocity(Vector2f{ 0,JUMP_POWER });
		m_JumpClock += elapsedSec;
	}
}

void Player::UpdateKeyboard(float elapsedSec)
{
	Transform* playerTransform{ this->GetTransform() };
	const float accelSpeed{ ACCELERATION_SPEED * elapsedSec };
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
	Jump(pStates[SDL_SCANCODE_SPACE],elapsedSec);

	this->MoveTo(elapsedSec, direction.Normalized(), MOVEMENT_SPEED * currentAccelerationRatio);
}

