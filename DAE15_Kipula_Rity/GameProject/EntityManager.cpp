#include "pch.h"
#include "EntityManager.h"
#include "Entity.h"
#include "AnimationController.h"
#include "Scene.h"
#include "CollisionHandler.h"

EntityManager::EntityManager(Scene* scene) :
	m_Entities{},
	m_pScene{scene}
{

}

EntityManager::~EntityManager()
{
	for (size_t idx{ 0 }; idx < m_Entities.size(); idx++) {
		//RemoveEntity(m_Entities[idx]);
		delete m_Entities[idx];
		//m_Entities[idx] = nullptr;
	};
}
void EntityManager::DrawEntities() const
{
	for (size_t entityIndex{0}; entityIndex < m_Entities.size();entityIndex++){
		//std::cout << m_Entities[entityIndex]->GetName() << " #" << entityIndex << std::endl;
		if (m_Entities[entityIndex] != nullptr) {
			m_Entities[entityIndex]->Draw();
		};
	};
}


void EntityManager::UpdateEntities(float elapsedSec)
{
	for (size_t entityIndex{0}; entityIndex < m_Entities.size(); entityIndex++) { // change these to for i
		if (m_Entities[entityIndex] != nullptr) {
			m_Entities[entityIndex]->Update(elapsedSec);
		}
	};
}

void EntityManager::AddEntity(Entity* entity)
{
	m_pScene->GetCollisionHandler()->AddBody(new CollisionBody(entity));
	entity->GetCollisionBody()->SetTag("Entity");
	m_Entities.push_back(entity);
}

void EntityManager::RemoveEntity(Entity* entity) 
{
	for (size_t entityIndex{}; entityIndex < m_Entities.size();entityIndex++){
		if (m_Entities[entityIndex] == entity) {
			//std::cout << "Removed " << entity->GetName() << std::endl;
			//delete m_Entities[entityIndex];
			m_pScene->GetCollisionHandler()->RemoveBody(entity);
			m_Entities[entityIndex] = nullptr;
			//m_Entities.erase(m_Entities.begin() + entityIndex);
			break;
		}
	}
}
