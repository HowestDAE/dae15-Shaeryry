#include "pch.h"
#include "Enemy.h"
#include "EntityManager.h"
#include "Transform.h"
#include "CollisionBody.h"

Enemy::Enemy(EntityManager* entityManager, const Vector2f& origin, const std::string& entityName)
	:
	Entity(entityManager, origin, entityName),
	m_IsVisible{ false },
	m_SavedDirection{ false },
	m_Clock{ 0 },
	m_Speed{ 0 },
	m_SpecialCooldown{ DEFAULT_ENEMY_ABILITY_COOLDOWN },
	m_SpecialClock{ m_SpecialCooldown }
{
	this->GetTransform()->SetWidth(DEFAULT_ENTITY_WIDTH);
	this->GetTransform()->SetHeight(DEFAULT_ENTITY_HEIGHT);

	//SetState(EntityState::Run);
}

void Enemy::Update(float elapsedSec)
{
	Entity::Update(elapsedSec);
	this->GetTransform()->ApplyPhysics(elapsedSec);
	m_SpecialClock += elapsedSec;
	m_Clock += elapsedSec;
}

void Enemy::GoToTarget(float elapsedSec, Entity* target)
{
	const bool powerActivated{ m_pPower != nullptr  and m_pPower->IsActive() };
	if (not powerActivated) {
		SetTargetDirection(target);

		this->SetState(EntityState::Run);
		this->MoveTo(elapsedSec, m_TargetDirection.Normalized(), m_Speed);

		const Vector2f wallNormal{ this->GetCollisionBody()->GetFrontCollisionNormal() };
		const float wallToTargetDOT{ wallNormal.DotProduct(m_TargetDirection.Normalized()) };
		const bool facingWall{ wallToTargetDOT < 0 };

		if (this->GetCollisionBody()->IsWallbound() and facingWall) { 
			m_TargetDirection *= -1;
		}
	}
}

void Enemy::AttackTarget(Entity* target)
{
	const CollisionBody* collisionBody{ GetCollisionBody() }; 
	const std::vector<Entity*> targets{ this->m_pManager->CastHitbox( this ,collisionBody->GetRect() ) };
	//std::cout << targets.size() << std::endl;

	const bool inRange{ std::find(targets.begin(),targets.end(),target) != targets.end() };
	if (inRange) {
		bool damagedTarget{ target->TakeDamage(1) };
		if (damagedTarget) {
			this->TakeDamage(1);
		}
	} 
}

void Enemy::SpecialAttack(Entity* target)
{
	if (CanUseSpecial()) {
		m_SpecialClock = 0;
	};
}

void Enemy::SetTargetDirection(Entity* target)
{
	if (!m_SavedDirection) {
		m_TargetDirection = GetDirectionVector(this, target) * 5;
		m_SavedDirection = true;
	};
}

Vector2f Enemy::GetDirectionVector(Entity* entity1, Entity* entity2)
{
	const Vector2f positionEntity_1{ entity1->GetTransform()->GetPosition() };
	const Vector2f positionEntity_2{ entity2->GetTransform()->GetPosition() };

	return Vector2f(positionEntity_2-positionEntity_1);

}

