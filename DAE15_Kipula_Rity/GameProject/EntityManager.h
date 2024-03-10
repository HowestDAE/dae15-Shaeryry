#pragma once
#include <utils.h>
#include <vector> 

class Entity;
class EntityManager
{
public:
	EntityManager(EntityManager* manager);
	~EntityManager();
	void AddEntity(Entity* entity);
private:
	std::vector<Entity*> m_Entities;
};

