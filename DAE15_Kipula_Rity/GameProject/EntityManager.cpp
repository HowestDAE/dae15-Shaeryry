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
void EntityManager::DrawEntities() const
{
	for (size_t entityIndex{0}; entityIndex < m_Entities.size();entityIndex++){
		//std::cout << m_Entities[entityIndex]->GetName() << " #" << entityIndex << std::endl;
		m_Entities[entityIndex]->Draw();
	};
}


void EntityManager::UpdateEntities(float elapsedSec)
{
	for (size_t entityIndex{0}; entityIndex < m_Entities.size(); entityIndex++) { // change these to for i
		m_Entities[entityIndex]->Update(elapsedSec);
	};
}

void EntityManager::AddEntity(Entity* entity)
{
	m_Entities.push_back(entity);
}
