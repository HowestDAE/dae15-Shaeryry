#pragma once
#include <utils.h>
#include <vector> 

class Entity;
class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	void AddEntity(Entity* entity);
	std::vector<Entity*> GetEntities() const { return m_Entities; };
private:
	std::vector<Entity*> m_Entities;
};

