#pragma once
#include <vector>

class Scene;
class Enemy;
class EnemySpawner;
class EnemySpawnerHandler
{
public:
	EnemySpawnerHandler(Scene* scene);
	~EnemySpawnerHandler();
	void Update(float elapsedSec);
	void CreateSpawner(EnemySpawner* newSpawner);
private:
	Scene* m_pScene;
	std::vector<EnemySpawner*> m_Spawners;
};

