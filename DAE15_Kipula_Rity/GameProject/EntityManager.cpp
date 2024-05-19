#include "pch.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"
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
		const bool canDraw{ 
			entity != nullptr 
			and not entity->CanRemove() 
		};
		if (canDraw) {
			//std::cout << entity->GetName() << " : " << canDraw << std::endl;
			entity->Draw();
		};
	};
}


void EntityManager::UpdateEntities(float elapsedSec)
{
	const bool playerDiedPause{ m_pScene->GetPlayer() != nullptr and m_pScene->GetPlayer()->IsDeathPause() };

	for (size_t entityIndex{0}; entityIndex < m_Entities.size(); entityIndex++) { // change these to for i
		Entity* entity{ m_Entities[entityIndex] };
		
		const bool Removing{ not entity->IsAlive() and entity->CanRemove() };
		const bool CanUpdate{ 
			entity != m_pScene->GetPlayer()
			and not playerDiedPause
			or entity == m_pScene->GetPlayer()
		};

		if (CanUpdate) {
			if (entity != nullptr and not Removing) {
				entity->Update(elapsedSec);
			}
			else if (entity != nullptr and Removing) {
				//std::cout << entity->GetName() << " died !" << std::endl;
				delete entity;
				entityIndex--;
			};
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
			m_pScene->GetCollisionHandler()->RemoveBody(entity);
			m_Entities.erase(m_Entities.begin() + entityIndex);
			break;
		}
	}
}

std::vector<Entity*> EntityManager::CastHitbox(const Entity* attacker,const Rectf& hurtbox)
{
	std::vector<Entity*> EntityList{ this->GetEntities() };
	std::vector<Entity*> EntitiesInBox{};
	for (size_t entityIndex{}; entityIndex < EntityList.size(); entityIndex++) {
		Entity* EntityAtIndex{ EntityList[entityIndex] };
		const CollisionBody* EntityBody{ EntityAtIndex->GetCollisionBody() };

		if (EntityBody->IsActive() && EntityAtIndex != attacker) {
			if (utils::IsOverlapping(hurtbox, EntityBody->GetRect())) {
				EntitiesInBox.push_back(EntityAtIndex);
			}
		}
	}

	return EntitiesInBox;
}

