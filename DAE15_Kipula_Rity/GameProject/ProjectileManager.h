#pragma once
#include "pch.h"
#include "utils.h"
#include "Projectile.h"
#include "Component.h"
#include <vector>

class EntityManager;
class ProjectileManager final : private Component
{
public:
	explicit ProjectileManager(Entity* owner,EntityManager* entityManager);
	ProjectileManager& operator=(const ProjectileManager& rhs) = delete;
	ProjectileManager(const ProjectileManager& other) = delete;
	~ProjectileManager();

	void Update(float elapsedSec);
	void UpdateDamage(Entity* attacker);
	void Draw() const;

	void AddProjectile(Projectile* newProjectile);
	void RemoveProjectile(Projectile* projectile);
private:
	Entity* m_pOwner;
	EntityManager* m_pEntityManager;
	std::vector<Projectile*> m_pProjectiles;
};

