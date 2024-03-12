#include "pch.h"
#include <iostream>
#include "Entity.h"
#include "EntityManager.h"
#include "AnimationController.h"

Entity::Entity(EntityManager* manager, const Vector2f& origin, const std::string& entityName) :
	m_pManager{ manager },
	m_pAnimator{ new AnimationController(this) },
	m_Position{ origin },
	m_Health{ 1 }
{
	SetName(entityName);
	manager->AddEntity(this);
}

Entity::~Entity() {
	delete m_pAnimator;
}

void Entity::Update(float elapsedSec)
{
	m_pAnimator->Update(elapsedSec);
}
