#pragma once
#include <utils.h>
#include <vector> 

class Entity;
class TextureManager;
class CollisionHandler;
class EntityManager
{
public:
	EntityManager(TextureManager* textureManager);
	~EntityManager();
	void DrawEntities() const;
	void UpdateEntities(float elapsedSec);
	void AddEntity(Entity* entity);
	std::vector<Entity*> GetEntities() const { return m_Entities; };
private:
	std::vector<Entity*> m_Entities;
	TextureManager* m_pTextureManager;
};

