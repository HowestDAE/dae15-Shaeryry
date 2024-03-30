#pragma once
#include <vector>
#include "utils.h"
#include "CollisionBody.h"

class Transform;
class Component;

/*struct CollisionBody {
	std::vector<Point2f> vertices;
	Transform* transform;
	Component* instance;
	bool active;
};*/

class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	//void Update(float elapsedSec);
	void AddBody(CollisionBody* newBody);
	void RemoveBody(Component* Instance);
	std::vector<CollisionBody*> GetBodies() const; // Maybe add tag system later?????
private:
	std::vector<CollisionBody*> m_Objects;
};

