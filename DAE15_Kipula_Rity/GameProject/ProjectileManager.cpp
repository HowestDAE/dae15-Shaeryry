#include "pch.h"
#include "utils.h"
#include "Scene.h"
#include "Projectile.h"
#include "Transform.h"
#include "Entity.h"
#include "EntityManager.h"
#include "CollisionHandler.h"
#include "CollisionBody.h"
#include "ProjectileManager.h"
#include "World.h"

ProjectileManager::ProjectileManager(Entity* owner, EntityManager* entityManager) :
	m_pOwner{ owner },
	m_pEntityManager{ entityManager }
{
}


ProjectileManager::~ProjectileManager()
{
	while (m_pProjectiles.size() > 0) {
		RemoveProjectile(m_pProjectiles[0]);
	}
}

void ProjectileManager::Update(float elapsedSec)
{
	for (size_t projectileIndex{}; projectileIndex < m_pProjectiles.size(); projectileIndex++) {
		Projectile* projectile{ m_pProjectiles[projectileIndex] };
		projectile->Update(elapsedSec);

		// Damage
		if (projectile->IsActive()) {
			const std::vector<Entity*> targets{ this->m_pEntityManager->CastHitbox( m_pOwner ,projectile->GetCollisionBody()->GetRect() )};
			std::cout << targets.size() << std::endl;
			for (size_t entityIndex{ 0 }; entityIndex < targets.size(); entityIndex++) {
				Entity* target{ targets[entityIndex] };
				bool damagedTarget{ target->TakeDamage(projectile->GetDamage()) };

				projectile->Destroy();
				break;
			}
		}
		//

		if (projectile->CanDelete()) {
			RemoveProjectile(projectile);
		}
	}
}

void ProjectileManager::Draw() const
{
	for (size_t projectileIndex{}; projectileIndex < m_pProjectiles.size(); projectileIndex++) {
		const Projectile* projectile{ m_pProjectiles[projectileIndex] };
		projectile->Draw();
	}
}

void ProjectileManager::AddProjectile(Projectile* newProjectile)
{
	m_pEntityManager->GetScene()->GetCollisionHandler()->AddBody(new CollisionBody(newProjectile));
	newProjectile->GetCollisionBody()->SetTag("Projectile");
	m_pProjectiles.push_back(newProjectile);
}

void ProjectileManager::RemoveProjectile(Projectile* projectile)
{
	for (size_t projectileIndex{}; projectileIndex < m_pProjectiles.size(); projectileIndex++) {
		Projectile* projectileAtIndex{ m_pProjectiles[projectileIndex] };
		if (projectile == projectileAtIndex) {
			m_pEntityManager->GetScene()->GetCollisionHandler()->RemoveBody(projectileAtIndex);
			delete projectileAtIndex;	
			m_pProjectiles.erase(m_pProjectiles.begin() + projectileIndex);
			break;
		}
	}
}
