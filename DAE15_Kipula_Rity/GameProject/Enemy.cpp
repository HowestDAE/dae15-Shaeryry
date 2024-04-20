#include "pch.h"
#include "Enemy.h"
#include "Transform.h"
#include "CollisionBody.h"

Enemy::Enemy(EntityManager* entityManager, const Vector2f& origin, const std::string& entityName)
	: 
	Entity(entityManager,origin,entityName),
	m_IsVisible{false}
{
	this->GetTransform()->SetWidth(DEFAULT_ENTITY_WIDTH);
	this->GetTransform()->SetHeight(DEFAULT_ENTITY_HEIGHT);

	//SetState(EntityState::Run);
}

void Enemy::Update(float elapsedSec)
{
	Entity::Update(elapsedSec);
	this->GetTransform()->ApplyPhysics(elapsedSec);
}

void Enemy::GoToTarget(float elapsedSec, Entity* target)
{
}

void Enemy::AttackTarget(Entity* target)
{
	const CollisionBody* collisionBody{ GetCollisionBody() };
	const std::vector<Entity*> targets{ this->CastHitbox( collisionBody->GetRect() ) };
	//std::cout << targets.size() << std::endl;

	const bool inRange{ std::find(targets.begin(),targets.end(),target) != targets.end() };
	if (inRange) {
		bool damagedTarget{ this->TakeDamage(1) };
		if (damagedTarget) {
			target->TakeDamage(1);
		}
	} 
}

Vector2f Enemy::GetDirectionVector(Entity* entity1, Entity* entity2)
{
	const Vector2f positionEntity_1{ entity1->GetTransform()->GetPosition() };
	const Vector2f positionEntity_2{ entity2->GetTransform()->GetPosition() };

	return Vector2f(positionEntity_2-positionEntity_1);

}

