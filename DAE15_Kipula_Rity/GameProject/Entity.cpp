#include "pch.h"
#include <iostream>
#include "Entity.h"
#include "EntityManager.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Transform.h"
#include <map>

Entity::Entity(EntityManager* manager, const Vector2f& origin, const std::string& entityName) :
	m_pManager{ manager },
	m_pAnimator{ new AnimationController(this) },
	m_pCoreAnimation{nullptr},
	m_State{ EntityState::None },
	m_OldState{ EntityState::None }
{
	this->SetName(entityName);
	this->GetTransform()->SetPosition(origin);
	manager->AddEntity(this);
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
}

void Entity::OnStateChanged()
{
	//Default Animation update for any entity
	if (m_pCoreAnimation != nullptr) {
		m_pCoreAnimation->DeleteAnimation();
		m_pCoreAnimation = nullptr;
	};

	AnimationData trackData{ m_AnimationsData.at(int(m_State)) };
	m_pCoreAnimation = m_pAnimator->PlayAnimation(trackData.name,trackData.frames,0);
	m_pCoreAnimation->Loop(trackData.loop);
}

void Entity::SetState(EntityState newState)
{
	m_State = newState;
	if (m_OldState != m_State) {
		//std::cout << "State has changed !!" << " : " << static_cast<int>(m_State) << std::endl;
		m_OldState = m_State;
		OnStateChanged();
	}
}
