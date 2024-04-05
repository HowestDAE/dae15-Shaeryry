#include "pch.h"
#include "Enemy.h"
#include "Transform.h"

Enemy::Enemy(EntityManager* entityManager, const Vector2f& origin, const std::string& entityName)
	: Entity(entityManager,origin,entityName)
{
	this->GetTransform()->SetWidth(40);
	this->GetTransform()->SetHeight(40);

	std::map<int, AnimationData> enemyTracks{};
	enemyTracks[2] = AnimationData{ "Run",2,Animation::DEFAULT_ANIMATION_UPDATE,true };
	this->SetAnimationData(enemyTracks);

	SetState(EntityState::Run);
}

void Enemy::Update(float elapsedSec)
{
	Entity::Update(elapsedSec);
	this->GetTransform()->ApplyPhysics(elapsedSec);
}

void Enemy::GoToTarget(float elapsedSec,Entity* target)
{
	this->MoveTo(elapsedSec,target->GetTransform()->GetPosition(),0);
}

void Enemy::AttackTarget(Entity* target)
{
}

