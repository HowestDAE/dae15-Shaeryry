#include "pch.h"
#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager() :
	m_Entities{}
{

}

EntityManager::~EntityManager()
{
	for (size_t idx{ 0 }; idx < m_Entities.size(); idx++) {
		delete m_Entities[idx];
		m_Entities[idx] = nullptr;
	};
} 

void EntityManager::AddEntity(Entity* entity)
{
	m_Entities.push_back(entity);
}
