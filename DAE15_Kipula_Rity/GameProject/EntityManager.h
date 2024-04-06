#pragma once
#include "pch.h"
#include <utils.h>
#include <vector> 

class Scene;
class Entity;
class TextureManager;
class CollisionHandler;
class EntityManager
{
public:
	EntityManager(Scene* scene);
	~EntityManager();
	void DrawEntities() const;
	void UpdateEntities(float elapsedSec);
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	std::vector<Entity*> GetEntities() const { return m_Entities; };
private:
	Scene* m_pScene;
	std::vector<Entity*> m_Entities;
};

