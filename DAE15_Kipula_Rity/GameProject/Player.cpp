#include "pch.h"
#include "Player.h" 
#include "ProjectileManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Transform.h"
#include "CollisionBody.h"

// Projectiles
#include "Star.h"
//

#include <map>

Player::Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName) :
	Entity(manager, origin, entityName),
	m_JumpClock{ 0 },
	m_RunClock{ 0 },
	m_ShootingClock{ KIRBY_SHOOTING_TIME },
	m_DeflateClock{ KIRBY_DEFLATE_TIME },
	m_Jumping{ false },
	m_Sucking{ false },
	m_SuckingTargets{ false },
	m_Absorbed{false},
	m_CanShoot{false},
	m_PressedSpace{false},
	m_Shooter{ new ProjectileManager(this,m_pManager) }
{ 
	this->SetHealth(6);
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
	playerTracks[7] = AnimationData{ "Sucking",1,DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[static_cast<int>(EntityState::BigIdle)] = AnimationData{ "Big_Idle",1,DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[static_cast<int>(EntityState::BigRun)] = AnimationData{ "Big_Run",4,KIRBY_BIG_RUN_UPDATE,true,0 };
	playerTracks[static_cast<int>(EntityState::BigJump)] = AnimationData{ "Big_Jump",4,DEFAULT_ANIMATION_UPDATE,true };
	playerTracks[static_cast<int>(EntityState::BigLanded)] = AnimationData{ "Big_Landed",1,DEFAULT_ANIMATION_UPDATE,false,2 };
	playerTracks[static_cast<int>(EntityState::BigFreefall)] = AnimationData{ "Big_Freefall",1,DEFAULT_ANIMATION_UPDATE,true };

	 
	this->SetAnimationData(playerTracks);
}

Player::~Player()
{
	delete m_Shooter;
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
		case SDLK_w:
			Shoot();
			SuckStart();
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
		case SDLK_w:
			SuckEnd();
			if (IsFull()) {
				m_CanShoot = true;
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
	const bool wasSucking{m_Sucking};


	// Default Update

	Entity::Update(elapsedSec);

	// Keyboard

	this->UpdateKeyboard(elapsedSec);

	// Physics && Movement

	this->GetTransform()->ApplyPhysics(elapsedSec);

	// Update States
	
	if (IsBig()) {
		this->GetTransform()->SetWidth(KIRBY_ENTITY_BIG_WIDTH);
		this->GetTransform()->SetHeight(KIRBY_ENTITY_BIG_HEIGHT);
	} else {
		this->GetTransform()->SetWidth(DEFAULT_ENTITY_WIDTH);
		this->GetTransform()->SetHeight(DEFAULT_ENTITY_HEIGHT);
	};

	const Vector2f currentVelocity{ playerTransform->GetCurrentVelocity() };
	EntityState currentState{ m_State };
	EntityState nextState{ m_State };

	const bool IsRunning{ abs(currentVelocity.x) > 0 };
	const bool IsFalling{ currentVelocity.y < 0 };

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
		if (not IsFull()) {
			if (IsRunning) { // Run
				nextState = EntityState::Run;
			}
			else {
				nextState = EntityState::Idle; // Default idle state !
			}
		}
		else {
			if (IsRunning) { // Run
				nextState = EntityState::BigRun;
			}
			else {
				nextState = EntityState::BigIdle; // Default idle state !
			}
		}
		
		 
		// Landing
		if (InAir()) { // Checks if the current state is in the air when you're just grounded !
			if (not IsFull()) {
				nextState = EntityState::Landed;
			}
			else {
				nextState = EntityState::BigLanded;
			}
		}
	} else { //  Air Logic
			// Falling
		if (IsFalling) { // Checks if Y motion is negative, which means you're falling !
			if (not IsFull()) {
				nextState = EntityState::Freefall;
			}
			else {
				nextState = EntityState::BigFreefall;
			}
		}
		// Jumping
		if (m_Jumping) {
			if (not IsFull()) {
				nextState = EntityState::Jump;
			}
			else {
				nextState = EntityState::BigJump;
			}
		}
	}
	


	// Sucking
	if (m_Sucking) {
		Suck();
		nextState = EntityState::Sucking;
	}
	else {
		m_DeflateClock += elapsedSec;
	}
	
	// FIX THIS FREAK AH FUCKING SUCKING GLITCH :>

	SetState(nextState);

	// State Actions  

	currentState = m_State; // Update the variable because it could've potentially changed !

	// Landing Event
	if (currentState == EntityState::Landed or currentState == EntityState::BigLanded) {
		m_JumpClock = 0;
		m_Jumping = false;
		if (not IsFull()) {
			SetState(EntityState::Idle);
		}
		else {
			SetState(EntityState::BigIdle);
		}
	};
	
	// Run Actions
		// Run Clock 
		if (currentState == EntityState::Run or currentState == EntityState::BigRun) {
			m_RunClock += elapsedSec;
		}
		else {
			m_RunClock = 0;
		}

		// Big Bounce on Run
		if (currentState == EntityState::BigRun) {
			if (m_pCoreAnimation != nullptr) {
				//const float bounceRythm{ sin(5.25f*m_RunClock) };
				//const float roundedRythm{ std::round(abs(bounceRythm)) };
				//const float currentBounceOffset{ 3.5f * roundedRythm };
				//std::cout << currentBounceOffset << " : " << m_RunClock << std::endl;
				const float timeForBounce{ m_pCoreAnimation->GetAnimationUpdateTime()*2 };
				const float timeRatio{ (m_RunClock / timeForBounce) };
				const float bounceRythm{ std::round( sin(float(M_PI*timeRatio)) ) };
				const float offset{ 3.5f + (3.5f * abs(bounceRythm)) };

				//std::cout << bounceRythm << " : " << m_RunClock << std::endl;

				m_pCoreAnimation->SetOffset(Vector2f(0, -offset));
			}
		}
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
	if (not IsFull()) {
		if (playerTransform->GetCurrentVelocity().x <= 0 && abs(alphaCurrentVelocity.x) > 0 && GetCollisionBody()->IsWallbound()) {
			if (playerTransform->GetAcceleration() >= 50) {
				//std::cout << "Wall oomf chan" << std::endl;
				playerTransform->SetAcceleration(0);
				m_pAnimator->PlayAnimation("Squish", 1, 1)->SetUpdateTime(KIRBY_SQUISH_TIME);
			}
		}
	}
	

	// Invicibility manager
	const bool Invincible{
		m_SuckingTargets,
	};
	SetInvincible(Invincible);

	// Shooting 
	m_ShootingClock += elapsedSec;

	// Update Projectiles

	m_Shooter->Update(elapsedSec);

	// Finish
	m_SuckingTargets = false;
}

void Player::Draw() const
{
	m_Shooter->Draw();
	Entity::Draw();
}

bool Player::CanControl() const
{
	return 
		not IsHitstunned() 
		and not IsSucking()
		and not IsDeflating();
}

bool Player::InAir()
{
	return 
		m_State == EntityState::Jump
		or m_State == EntityState::FallingDown
		or m_State == EntityState::Freefall;
}

bool Player::IsHitstunned() const
{
	return (m_TimeElapsedLastHit < KIRBY_STUN_TIME);
}

bool Player::IsDeflating() const
{
	return (m_DeflateClock < KIRBY_DEFLATE_TIME);
}

bool Player::IsBig() const
{
	return 
		IsSucking()
		or IsDeflating()
		or IsFull()
		or IsShooting(); // Check if you're shooting
}

bool Player::IsShooting() const
{
	return (m_ShootingClock < KIRBY_SHOOTING_TIME);
}

void Player::Jump()
{	
	if (!m_Jumping && !InAir() && CanControl()) {
		m_JumpClock = 0;
		m_Jumping = true;
		GetTransform()->SetVelocity(Vector2f{ GetTransform()->GetVelocity().x ,0 });
	}
}

void Player::JumpEnd()
{
	if (m_Jumping) {
		if (not IsFull()) {
			m_pAnimator->PlayAnimation("FallingDown", 5, 1)->SetUpdateTime((DEFAULT_ANIMATION_UPDATE * .75f));
		}
		m_Jumping = false;
	}

}

void Player::SuckStart()
{
	if (CanControl()) {
		if (not m_Sucking and not IsFull() and not IsShooting()) {
			m_pAnimator->PlayAnimation("SuckStart", 2, 3)->SetUpdateTime(DEFAULT_ANIMATION_UPDATE);
			m_Sucking = true;
		}
	}
}

void Player::Suck()
{
	if (not IsFull()) {
		const Vector2f suckOrigin{ this->GetTransform()->GetPosition() };

		for (size_t entityIndex{}; entityIndex < m_pManager->GetEntities().size(); entityIndex++) {
			Entity* entityAtIndex{ m_pManager->GetEntities()[entityIndex] };
			if (entityAtIndex != this) {

				const Vector2f enemyPosition{ entityAtIndex->GetTransform()->GetPosition() };
				const Vector2f playerToEnemyVector{ (enemyPosition - suckOrigin) };
				const float distance{ playerToEnemyVector.Length() };
				// check if you're facing the enemy with DOT product

				const Vector2f lookVector{ Vector2f(this->GetTransform()->GetLookDirection(),0)};
				const Vector2f enemyVector{ (enemyPosition - suckOrigin) };

				float DOT{ enemyVector.Normalized().DotProduct(lookVector.Normalized())};
				if (distance < KIRBY_ABSORB_RANGE and (DOT > 0)) {
					entityAtIndex->GetTransform()->ApplyImpulse(playerToEnemyVector.Normalized() * -KIRBY_ABSORB_POWER);

					if (distance < KIRBY_EAT_RANGE) {
						m_Absorbed = true;
						m_AbsoredPower = entityAtIndex->GetPower();
						entityAtIndex->SetHealth(0);
						SuckEnd();
					}

					m_SuckingTargets = true;
					//break;
				}
			}
		}
	}
	
}

void Player::SuckEnd()
{
	if (m_Sucking) {
		if (!IsFull()) {
			m_pAnimator->PlayAnimation("SuckEnd", 2, 3)->SetUpdateTime(DEFAULT_ANIMATION_UPDATE);
			m_DeflateClock = 0;
		}
		m_Sucking = false;
		m_CanShoot = false;
	}
}

void Player::Shoot()
{
	if (IsFull() and not IsShooting() and m_CanShoot) {
		m_Absorbed = false;
		const Transform* playerTransform{ this->GetTransform() };
		const Vector2f origin{ playerTransform->GetPosition() + Vector2f(playerTransform->GetWidth()/2,DEFAULT_ENTITY_HEIGHT/2) };
		const Vector2f target{ origin + Vector2f(100 * playerTransform->GetLookDirection(),0) };
		m_pAnimator->PlayAnimation("GroundShoot", 4, 3)->SetUpdateTime(KIRBY_SHOOT_GROUND_ANIMATION_UPDATE);

		m_Shooter->AddProjectile(new Star(origin, target, 5));
		m_ShootingClock = 0;
	}
}

void Player::OnDamage()
{
	Entity::OnDamage();
	m_Sucking = false;
	m_DeflateClock = KIRBY_DEFLATE_TIME;

	const Vector2f direction{ 1*this->GetTransform()->GetLookDirection(),0};
	const Vector2f incomingVelocity{ this->GetTransform()->GetCurrentVelocity() + direction };
	const Vector2f outgoingVelocity{ (incomingVelocity * 100).Normalized() * -KIRBY_KNOCKBACK_ON_HIT};
	this->GetTransform()->SetVelocity(Vector2f());
	this->GetTransform()->ApplyImpulse( Vector2f(outgoingVelocity.x,-outgoingVelocity.y) );
	this->GetTransform()->SetFlipped(false);

	Animation* hurtAnimation;
	if (not IsFull()) {
		hurtAnimation = m_pAnimator->PlayAnimation("Hurt", 2, 3);
		hurtAnimation->SetUpdateTime(DEFAULT_ANIMATION_UPDATE);
		hurtAnimation->SetFlipped(true);
	}
	else {
		hurtAnimation = m_pAnimator->PlayAnimation("Big_Hurt", 1, 3);
		hurtAnimation->SetUpdateTime(DEFAULT_ANIMATION_UPDATE*2);
		hurtAnimation->SetFlipped(true);
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
		inputPressed = true;
	} else if (pStates[SDL_SCANCODE_LEFT]) {
		direction.x = -1;
		playerTransform->AddAcceleration(accelSpeed);
		inputPressed = true;
	};

	//m_Sucking = pStates[SDL_SCANCODE_Z]; // Sucking state update
	 
	if (CanControl()) {
		this->MoveTo(elapsedSec, direction.Normalized(), KIRBY_MOVEMENT_SPEED * currentAccelerationRatio);
	}
}

