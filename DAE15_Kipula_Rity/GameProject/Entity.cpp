#include "pch.h"
#include <iostream>
#include "Entity.h"
#include "EntityManager.h"
#include "Animation.h"
#include "CollisionHandler.h"
#include "AnimationController.h"
#include "Transform.h"
#include <map>

Entity::Entity(EntityManager* manager, const Vector2f& origin, const std::string& entityName) :
	m_pManager{ manager },
	m_pCoreAnimation{ nullptr },
	m_State{ EntityState::Idle },
	m_OldState{ EntityState::None },
	m_InAir{ false },
	m_Invincible{false},
	m_TimeElapsedLastHit{ 0 },
	m_Health{1}
{
	m_pAnimator = new AnimationController(this);

	this->SetName(entityName);
	this->GetTransform()->SetPosition(origin);

	m_pManager->AddEntity(this);
} 

Entity::~Entity() {
	// Remove entity from the manager !
	m_pManager->RemoveEntity(this);
	delete m_pAnimator;
}

void Entity::Draw() const
{		
	m_pAnimator->DrawAnimations();
}

void Entity::Update(float elapsedSec)
{
	m_pAnimator->UpdateAnimations(elapsedSec);
	GetTransform()->Update(elapsedSec);
	if (this->GetCollisionBody() != nullptr) {
		this->GetCollisionBody()->UpdateCollider(elapsedSec);
		GetCollisionBody()->ApplyDefaultCollisions();
	}
	m_TimeElapsedLastHit += elapsedSec;
}

void Entity::MoveTo(float elapsedSec, const Vector2f& direction , float speed)
{
	Transform* entityTransform{ this->GetTransform() };
	const Vector2f entityPosition{ entityTransform->GetPosition() };
	Vector2f movement{};
	float xPos{ ((direction.Normalized().x * speed) * elapsedSec) };
	float yPos{ ((direction.Normalized().y * speed) * elapsedSec) };
	movement.x = xPos;
	movement.y = yPos;

	Vector2f newPosition{ (entityPosition + movement) }; 
	float xDifference{ (newPosition - entityPosition).x };

	if (xDifference != 0) {
		entityTransform->SetFlipped(xDifference < 0);
	}
	if (!GetCollisionBody()->FrontCollision(newPosition)) {
		this->GetTransform()->SetPosition(newPosition);
	}
}

// State Methods


void Entity::OnStateChanged()
{
	//std::cout << int(m_State) << std::endl;
	const AnimationData trackData{ m_AnimationsData[int(m_State)] };
	//Default Animation update for any entity
	if (m_pCoreAnimation != nullptr) {
		//std::cout << m_pCoreAnimation->GetName() << " is already present" << std::endl;
		m_pCoreAnimation->DeleteAnimation();
		m_pCoreAnimation = nullptr;
	};

	Animation* animation{ m_pAnimator->PlayAnimation(trackData.name, trackData.frames, trackData.priority) };
	animation->SetUpdateTime(trackData.updateTime);
	animation->Loop(trackData.loop);
	animation->SetPingPong(trackData.pingpong);

	if (trackData.loop) {
		m_pCoreAnimation = animation;
		//std::cout << m_pCoreAnimation->GetName() << " is now present :D" << std::endl;

	}
}
 

void Entity::SetState(EntityState newState)
{
	m_State = newState;
	if (m_OldState != m_State) {
		m_OldState = m_State;
		OnStateChanged();
	}
}

bool Entity::TakeDamage(const int damage)
{
	if (CanDamage()) {
		int currentHealth{ m_Health };
		int newHealth{ currentHealth - damage };
		SetHealth(newHealth);

		OnDamage(); 

		if (newHealth <= 0 && currentHealth > 0) {
			OnDied();
		};

		m_TimeElapsedLastHit = 0;

		return true;
	}

	return false;
}

void Entity::OnDamage()
{
	//std::cout << "hit" << std::endl;
	m_TimeElapsedLastHit = 0;
}


void Entity::OnDied() {
	//std::cout << "ded" << std::endl;
}

void Entity::SetHealth(const int health)
{
	m_Health = health;
}

bool Entity::CanDamage() const
{
	return 
		(m_TimeElapsedLastHit > INVINCIBILITY_TIME)
		&& IsAlive()
		&& !IsInvincible();
}
