#pragma once
#include "pch.h"
#include <vector>

class Scene;
class Enemy;
class EnemySpawner;
class EnemySpawnerHandler final {
public:
	explicit EnemySpawnerHandler(Scene* scene);
	EnemySpawnerHandler& operator=(const EnemySpawnerHandler& rhs) = delete;
	EnemySpawnerHandler(const EnemySpawnerHandler& other) = delete;
	EnemySpawnerHandler(EnemySpawnerHandler&& other) = delete;
	EnemySpawnerHandler& operator=(EnemySpawnerHandler&& other) = delete;
	~EnemySpawnerHandler();

	void Update(float elapsedSec);
	void CreateSpawner(EnemySpawner* newSpawner);
private:
	Scene* m_pScene;
	std::vector<EnemySpawner*> m_Spawners;
};

