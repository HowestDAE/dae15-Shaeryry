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
	while (m_Entities.size() > 0) {
		delete m_Entities[0];
	}
}
void EntityManager::DrawEntities() const
{
	for (size_t entityIndex{ m_Entities.size() }; entityIndex > 0; entityIndex--) {
		//std::cout << m_Entities[entityIndex]->GetName() << " #" << entityIndex << std::endl;
		const size_t index{ (entityIndex - 1) };
		const Entity* entity{ m_Entities[index] };
		const bool canDraw{ entity != nullptr && entity->IsAlive() };
		//std::cout << entity->GetName() << " : " << canDraw << std::endl;
		if (canDraw) {
			entity->Draw();
		};
	};
}


void EntityManager::UpdateEntities(float elapsedSec)
{
	for (size_t entityIndex{0}; entityIndex < m_Entities.size(); entityIndex++) { // change these to for i
		Entity* entity{ m_Entities[entityIndex] };
		if (entity != nullptr && entity->IsAlive()) {
			entity->Update(elapsedSec);

			if (!entity->IsAlive()) {
				delete entity;
				entityIndex -=1;
			}
		};
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
			m_pScene->GetCollisionHandler()->RemoveBody(entity);
			m_Entities.erase(m_Entities.begin() + entityIndex);
			break;
		}
	}
}
