#include "pch.h"
#include <iostream>
#include "Entity.h"
#include "EntityManager.h"
#include "AnimationController.h"

Entity::Entity(EntityManager* manager, const Vector2f& origin, const std::string& entityName) :
	m_pManager{ manager },
	m_pAnimator{ new AnimationController(this) },
	m_Position{ origin },
	m_State{ EntityState::None },
	m_GravityAffected{ true }
{
	SetName(entityName);
	manager->AddEntity(this);
}

Entity::~Entity() {
	delete m_pAnimator;
}

void Entity::Draw() const
{
	m_pAnimator->DrawAnimations();
}

void Entity::Update(float elapsedSec)
{
	m_pAnimator->UpdateAnimations(elapsedSec);
	if (m_GravityAffected) {

	};
}
