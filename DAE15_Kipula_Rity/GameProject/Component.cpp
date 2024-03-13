#include "pch.h"
#include "Component.h"
#include "Transform.h"

Component::Component() :
	m_pParent{ nullptr },
	m_pTransform{ new Transform() }
{
}

Component::~Component()
{
	delete m_pTransform;
}

