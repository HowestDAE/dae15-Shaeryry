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
	m_InAir{ false }
{
	this->SetName(entityName);
	this->GetTransform()->SetPosition(origin);
	manager->AddEntity(this);
	m_pAnimator = new AnimationController(this);
}

Entity::~Entity() {
	// Remove entity from the manager !
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
	const AnimationData trackData{ m_AnimationsData[int(m_State)]};
	//Default Animation update for any entity
	if (m_pCoreAnimation != nullptr) {
		m_pCoreAnimation->DeleteAnimation();
		m_pCoreAnimation = nullptr;
	};

	Animation* animation = m_pAnimator->PlayAnimation(trackData.name, trackData.frames, trackData.priority);
	animation->SetUpdateTime(trackData.updateTime);
	animation->Loop(trackData.loop);

	if (trackData.loop) {
		m_pCoreAnimation = animation;
	}
	
}

void Entity::SetState(EntityState newState)
{
	//std::cout << m_AnimationsData.size() << std::endl;
	m_State = newState;
	if (m_OldState != m_State) {
		//std::cout << "State has changed !!" << " : " << static_cast<int>(m_State) << std::endl;
		m_OldState = m_State;
		OnStateChanged();
	}
}
