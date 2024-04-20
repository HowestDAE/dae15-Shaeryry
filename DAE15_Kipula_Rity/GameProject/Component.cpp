#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "CollisionBody.h"

Component::Component() :
	m_pParent{ nullptr },
	m_pTextureManager{ nullptr },
	m_pTransform{ new Transform() },
	m_pCollisionBody{ nullptr }
{
}

Component::~Component()
{
	if (m_pCollisionBody != nullptr) {
		delete m_pCollisionBody;
	}
	delete m_pTransform;
}
