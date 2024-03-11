#include "pch.h"
#include "Entity.h"
#include "EntityManager.h"
#include "AnimationController.h"

Entity::Entity(EntityManager* manager, const Vector2f& origin, const int entityId) :
	m_pManager{ manager },
	m_pAnimator{ new AnimationController() },
	m_Position{ origin },
	m_EntityId{ static_cast<EntityId>(entityId) },
	m_Health{ 1 }
{
	manager->AddEntity(this);
}

Entity::~Entity() {
	delete m_pAnimator;
}

void Entity::Update(float elapsedSec)
{
	m_pAnimator->Update(elapsedSec);
}
