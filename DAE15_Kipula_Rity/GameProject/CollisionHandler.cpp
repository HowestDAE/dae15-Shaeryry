#include "pch.h"
#include <iostream>
#include "utils.h"
#include "CollisionHandler.h"
#include "CollisionBody.h"
#include "Transform.h"
#include "Component.h"

CollisionHandler::CollisionHandler()
	: m_Objects{}
{
}

CollisionHandler::~CollisionHandler()
{
}


void CollisionHandler::AddBody(CollisionBody* newBody)
{
	if (newBody != nullptr) {
		newBody->GetComponent()->SetCollisionBody(newBody);
		newBody->SetCollisionHandler(this);
		m_Objects.push_back(newBody);
	}
}

void CollisionHandler::RemoveBody(Component* Instance)
{
	for (size_t indexBody{}; indexBody < m_Objects.size(); ++indexBody) {
		if (m_Objects[indexBody]->GetComponent() == Instance) {
			delete m_Objects[indexBody];
			m_Objects.erase(m_Objects.begin() + indexBody);
			break;
		}
	}
}

std::vector<CollisionBody*> CollisionHandler::GetBodies() const
{
	return m_Objects;
}

