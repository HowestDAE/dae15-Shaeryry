#pragma once
#include <utils.h>

enum class EntityId {
	Kirby = 0,
};

class EntityManager;
class AnimationController;
class Entity
{
public:
	Entity(
		EntityManager* manager,
		const Vector2f& origin = Vector2f{ 0,0 },
		const int entityId = 0
	);
	~Entity();
	virtual void Update(float elapsedSec);
	//virtual void Draw() const;

	AnimationController* GetAnimator() const { return m_pAnimator; };
protected:
	AnimationController* m_pAnimator;
	EntityManager* m_pManager;
	EntityId m_EntityId;
	Vector2f m_Position{};
	int m_Health;
};


