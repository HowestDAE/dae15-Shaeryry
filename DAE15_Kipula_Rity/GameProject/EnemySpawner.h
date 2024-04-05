#pragma once
#include <vector>
#include "Component.h"
#include "Enemy.h"

class Camera;
class EntityManager;
class EnemySpawner : public Component
{
public:
	EnemySpawner(const EnemyType typeSpawner,const Vector2f& position,const int amountEnemies);
	void Update(float elapsedSec,const Camera* camera);
	void AddEnemy(Enemy* enemy);
	void RemoveEnemy(Enemy* enemy);
	bool CanSpawn(const Camera* camera);

	EnemyType GetSpawnerType() const { return m_SpawnerType; };

private:
	int m_MaxEnemies;
	std::vector<Enemy*> m_SpawnedEnemies;
	EnemyType m_SpawnerType;
};

