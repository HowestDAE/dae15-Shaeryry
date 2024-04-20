#pragma once
#include "pch.h"
#include <utils.h>
#include <vector> 

class Scene;
class Entity;
class TextureManager;
class CollisionHandler;
class EntityManager final {
public:
	explicit EntityManager(Scene* scene);
	EntityManager& operator=(const Entity& rhs) = delete;
	EntityManager(const Entity& other) = delete;
	~EntityManager();

	void DrawEntities() const;
	void UpdateEntities(float elapsedSec);
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);

	std::vector<Entity*> CastHitbox(const Entity* attacker,const Rectf& hurtbox);
	std::vector<Entity*> GetEntities() const { return m_Entities; };
	Scene* GetScene() const { return m_pScene; }
private:
	Scene* m_pScene;
	std::vector<Entity*> m_Entities;
};

