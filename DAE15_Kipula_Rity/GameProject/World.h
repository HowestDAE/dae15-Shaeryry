#pragma once
#include "pch.h"
#include <utils.h>
#include <Texture.h>
#include <vector>
#include "Component.h"
#include "Enemy.h"
#include "CollisionHandler.h"
#include <map>

struct SpawnerData {
	Vector2f position;
	EnemyType typeSpawner;
	int amountEnemies;
};

struct Door {
	Rectf area;
	std::string world;
};


struct WorldData {
	std::string name;
	float scale;
	int frames;
	float updateFrames;
	std::vector<SpawnerData> spawners;
	std::vector<Door>doors;
};

class Camera;
class World final : public Component 
{
public:
	explicit World(const WorldData& worldData,TextureManager* textureManager);
	World& operator=(const World& rhs) = delete;
	World(const World& other) = delete;

	~World();	
	void Draw() const;
	void Update(float elapsedSec); 

	// Setter
	void SetWorldScale(float scale) { m_WorldScale = scale; };

	// Getters
	std::vector<Door> GetDoors() const { return m_Doors; };
	Rectf GetWorldRect() { return m_WorldRect; };
	float GetWorldScale() { return m_WorldScale; };
	void CreateCollisions( CollisionHandler* collisionHandler );

	std::vector<std::vector<Point2f>> GetWorldVertices() const { return m_CollisionData; };
	std::vector<CollisionBody*> GetPlatforms() const { return m_Platforms; };
private:
	std::string GetWorldTexturePath();

	// Variables
	std::vector<CollisionBody*> m_Bodies;
	std::vector<CollisionBody*> m_Platforms;
	std::vector<std::vector<Point2f>> m_CollisionData;
	std::vector<std::vector<Point2f>> m_PlatformsData;
	std::vector<Door> m_Doors;

	WorldData m_Data;
	Texture* m_pWorldTexture;
	Rectf m_WorldRect;
	float m_WorldScale;
	float m_WorldElapsedTime;
};

