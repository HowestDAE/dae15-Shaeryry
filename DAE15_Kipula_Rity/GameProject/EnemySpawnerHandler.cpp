#include "pch.h"
#include "Transform.h"
#include "EnemySpawnerHandler.h"
#include "EnemySpawner.h"
#include "Enemy.h"
#include "Scene.h"
#include "Camera.h"

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
		// Check if spawner can spawn enemies !
		if (currentSpawner->CanSpawn(m_pScene->GetCamera())) {
			switch (currentSpawner->GetSpawnerType())
			{	
				case EnemyType::WaddleDoo:
					currentSpawner->AddEnemy(new Enemy(m_pScene->GetEntityManager(), currentSpawner->GetTransform()->GetPosition(), "Waddle Doo")); // Replace with waddle doo object later !
					break;
				default:
					break;
			}
		}

		currentSpawner->Update(elapsedSec, m_pScene->GetCamera());
	}
}

void EnemySpawnerHandler::CreateSpawner(EnemySpawner* newSpawner)
{
	m_Spawners.push_back(newSpawner);
}
