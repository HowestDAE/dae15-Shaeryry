#pragma once
#include "pch.h"
#include <utils.h>
#include <Texture.h>
#include <vector>
#include "Component.h"
#include "Enemy.h"
#include <map>

struct SpawnerData {
	Vector2f position;
	EnemyType typeSpawner;
	int amountEnemies;
};

struct WorldData {
	std::string name;
	float scale;
	float frames;
	std::vector<SpawnerData> spawners;
};

class Camera;
class World : public Component
{
public:
	World(const WorldData& worldData,TextureManager* textureManager);
	~World();
	void Draw() const;
	void Update(float elapsedSec);

	// Getters
	void SetWorldScale(float scale) { m_WorldScale = scale; }
	Rectf GetWorldRect() { return m_WorldRect; };
	float GetWorldScale() { return m_WorldScale; }
	std::vector<std::vector<Point2f>> GetWorldVertices() const { return m_CollisionData; };
private:
	std::string GetWorldTexturePath();
	std::vector<std::vector<Point2f>> m_CollisionData;
	Texture* m_pWorldTexture;
	Rectf m_WorldRect;
	float m_WorldScale;
};

