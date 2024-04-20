#include "pch.h"
#include "Transform.h"
#include "EnemySpawnerHandler.h"
#include "EnemySpawner.h"
#include "Enemy.h"
#include "Scene.h"
#include "Camera.h"
#include "Player.h"
#include "WaddleDoo.h"

EnemySpawnerHandler::EnemySpawnerHandler(Scene* scene):
	m_pScene{scene}
{

}

EnemySpawnerHandler::~EnemySpawnerHandler()
{
	for (size_t spawnerIndex{}; spawnerIndex < m_Spawners.size(); spawnerIndex++) {
		delete m_Spawners[spawnerIndex];
		m_Spawners[spawnerIndex] = nullptr;
	}
}

void EnemySpawnerHandler::Update(float elapsedSec)
{
	for (size_t spawnerIndex{}; spawnerIndex < m_Spawners.size(); spawnerIndex++) {
		EnemySpawner* currentSpawner{ m_Spawners[spawnerIndex] };
		const bool spawnerOnScreen{ m_pScene->GetCamera()->IsPointOnScreen(currentSpawner->GetTransform()->GetPosition().ToPoint2f()) };
		const bool canSpawnEnemies{ currentSpawner->CanSpawn(m_pScene->GetCamera()) };

		// Check if spawner was already on screen or if it just came on screen
		if (spawnerOnScreen) {
			if (!currentSpawner->IsVisible()) {
				// Check if spawner can spawn enemies !
				if (canSpawnEnemies) {
					const Vector2f spawnPosition{ currentSpawner->GetTransform()->GetPosition() };

					switch (currentSpawner->GetSpawnerType())
					{
						case EnemyType::WaddleDoo:
							currentSpawner->AddEnemy(new WaddleDoo(m_pScene->GetEntityManager(), spawnPosition));
							break;
						default:
							break;
					}
				}
			}

			currentSpawner->SetVisible(true);
		}
		else {
			currentSpawner->SetVisible(false);
		}
		
		// Handle enemy logic & behaviour
		std::vector<Enemy*> enemyVector{ currentSpawner->GetEnemies() };
		for (size_t enemyIndex{}; enemyIndex < enemyVector.size(); enemyIndex++) {
			Enemy* enemyAtIndex{ enemyVector[enemyIndex] };
			if (enemyAtIndex->IsAlive()) {
				enemyVector[enemyIndex]->GoToTarget(elapsedSec, m_pScene->GetPlayer());
				enemyVector[enemyIndex]->AttackTarget(m_pScene->GetPlayer());
			}
		}

		currentSpawner->Update(elapsedSec, m_pScene->GetCamera());
	}
}

void EnemySpawnerHandler::CreateSpawner(EnemySpawner* newSpawner)
{
	m_Spawners.push_back(newSpawner);
}
