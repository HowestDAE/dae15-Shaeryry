#include "pch.h"
#include "BrontoBurt.h"
#include "Enemy.h" 
#include "Entity.h"
#include "Transform.h"

BrontoBurt::BrontoBurt(EntityManager* entityManager, const Vector2f& origin) :
	Enemy(entityManager, origin, "Bronto Burt")
{
	std::map<int, AnimationData> brontoTracks{};
	brontoTracks[static_cast<int>(EntityState::Run)] = AnimationData{ "Run",2,BRONTO_ANIMATION_UPDATE,true };
	this->SetAnimationData(brontoTracks);

	SetPower(PowerTypes::None);
	m_Speed = BRONTO_MOVEMENT_SPEED;
	m_Score = 300;
}

void BrontoBurt::Update(float elapsedSec)
{
	Entity::Update(elapsedSec);
	m_SpecialClock += elapsedSec;
	m_Clock += elapsedSec;
}

void BrontoBurt::GoToTarget(float elapsedSec, Entity* target)
{
	SetTargetDirection(target);
	SetState(EntityState::Run);

	const float timePeriod{ (m_Clock / BRONTO_PERIOD) };
	const float sineMovement{ float( sin(M_PI * timePeriod)) };

	const float direction{ (abs(m_TargetDirection.x) / m_TargetDirection.x) };

	const Vector2f brontoDirection{
		(direction),
		(sineMovement*2.f)
	};

	const Vector2f currentPosition{ this->GetTransform()->GetPosition() };
	this->MoveTo(elapsedSec, brontoDirection, m_Speed);
}
