#pragma once
#include "pch.h"
#include <vector>
#include "utils.h"
#include "CollisionBody.h"

class Transform;
class Component;

class CollisionHandler final {
public:
	explicit CollisionHandler();
	CollisionHandler& operator=(const CollisionHandler& rhs) = delete;
	CollisionHandler(const CollisionHandler& other) = delete;
	~CollisionHandler();

	//void Update(float elapsedSec);
	void AddBody(CollisionBody* newBody);
	void RemoveBody(Component* Instance);
	std::vector<CollisionBody*> GetBodies() const; // Maybe add tag system later?????
private:
	std::vector<CollisionBody*> m_Objects;
};

