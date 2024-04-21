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
	int frames;
	std::vector<SpawnerData> spawners;
};

class Camera;
class World final : public Component 
{
public:
	explicit World(const WorldData& worldData,TextureManager* textureManager);
	World& operator=(const World& rhs) = delete;
	World(const World& other) = delete ;

	~World();	
	void Draw() const;
	void Update(float elapsedSec); 

	void SetWorldScale(float scale) { m_WorldScale = scale; }

	// Getters
	Rectf GetWorldRect() { return m_WorldRect; };
	float GetWorldScale() { return m_WorldScale; }
	std::vector<std::vector<Point2f>> GetWorldVertices() const { return m_CollisionData; };
private:
	std::string GetWorldTexturePath();
	std::vector<std::vector<Point2f>> m_CollisionData;
	WorldData m_Data;
	Texture* m_pWorldTexture;
	Rectf m_WorldRect;
	float m_WorldScale;
	float m_WorldElapsedTime;
};

