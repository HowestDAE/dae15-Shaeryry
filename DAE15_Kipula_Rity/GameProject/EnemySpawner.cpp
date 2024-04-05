#include "pch.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "Transform.h"
#include "Camera.h"

EnemySpawner::EnemySpawner(const EnemyType typeSpawner, const Vector2f& position, const int amountEnemies = 1) :
	m_SpawnerType{ typeSpawner },
	m_MaxEnemies{ amountEnemies }
{
	this->GetTransform()->SetPosition(position);
}

void EnemySpawner::Update(float elapsedSec,const Camera* camera)
{
	for (size_t enemyIndex{}; enemyIndex < m_SpawnedEnemies.size(); enemyIndex++) {
		Enemy* currentEnemy{ m_SpawnedEnemies[enemyIndex] };
		// Check for dead enemies !
		// Check if enemy isn't visible anymore !
		if (!camera->IsPointOnScreen(currentEnemy->GetTransform()->GetPosition().ToPoint2f())) { // if not on screen
			this->RemoveEnemy(currentEnemy);
		}
	};
}

void EnemySpawner::AddEnemy(Enemy* enemy)
{
	m_SpawnedEnemies.push_back(enemy);
}

void EnemySpawner::RemoveEnemy(Enemy* enemy)
{
	const bool HasSpawned{ std::find(m_SpawnedEnemies.begin(), m_SpawnedEnemies.end(), enemy ) != m_SpawnedEnemies.end() };
	if (HasSpawned) {
		for (size_t enemyIndex{}; enemyIndex < m_SpawnedEnemies.size(); enemyIndex++) {
			if (m_SpawnedEnemies[enemyIndex] == enemy) {
				std::cout << "Out of sight, out of mind !" << std::endl;
				//m_SpawnedEnemies[enemyIndex] = nullptr;
				delete m_SpawnedEnemies[enemyIndex];
				//m_SpawnedEnemies[enemyIndex] = nullptr;
				m_SpawnedEnemies.erase(m_SpawnedEnemies.begin() + enemyIndex);
				break;
			}
		}
	}
}

bool EnemySpawner::CanSpawn(const Camera* camera)
{
	const bool notMaxed{ m_SpawnedEnemies.size() < m_MaxEnemies };
	const bool isOnScreen{ camera->IsPointOnScreen(this->GetTransform()->GetPosition().ToPoint2f()) };
	return (notMaxed&&isOnScreen);
}
