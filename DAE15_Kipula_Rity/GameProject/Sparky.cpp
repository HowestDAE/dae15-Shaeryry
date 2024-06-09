#include "pch.h"
#include "Sparky.h"
#include "Entity.h"
#include "CollisionBody.h"
#include "AnimationController.h"
#include "Transform.h"

Sparky::Sparky(EntityManager* entityManager, const Vector2f& origin) :
	Enemy(entityManager, origin, "Sparky"),
	m_JumpClock{ 0 }
{
	std::map<int, AnimationData> sparkyTracks{};
	sparkyTracks[static_cast<int>(EntityState::Idle)] = AnimationData{ "Idle",1,SPARKY_ANIMATION_UPDATE,true };
	sparkyTracks[static_cast<int>(EntityState::Run)] = AnimationData{ "Run",3,SPARKY_ANIMATION_UPDATE,true };
	this->SetAnimationData(sparkyTracks);

	this->SetState(EntityState::Idle);
	SetPower(PowerTypes::None);
	m_Speed = SPARKY_MOVEMENT_SPEED;
	m_Score = 200;

}

void Sparky::GoToTarget(float elapsedSec, Entity* target)
{
	const bool powerActivated{ m_pPower != nullptr and m_pPower->IsActive() };
	if (not powerActivated) {

		const float jumpInterval{ 0.5f };
		const bool canJump{ (m_JumpClock > jumpInterval) };
		const bool windupJump{ m_JumpClock > (jumpInterval *.35f) };

		const bool airMovement{ abs(this->GetTransform()->GetCurrentVelocity().y) > 0.35f };
		//std::cout << this->GetTransform()->GetCurrentVelocity().y << std::endl;
		
		if (windupJump) { 
			this->GetAnimator()->PlayAnimation("Run", 3, 2);
		}
		 
		if (canJump) {
			SetTargetDirection(target);

			//this->SetState(EntityState::Run);

			const float direction{ (abs(m_TargetDirection.x) / m_TargetDirection.x) };
			const int jumpXDistance{ rand() % int(SPARKY_MOVEMENT_SPEED * 2) + int(SPARKY_MOVEMENT_SPEED) }; 
			this->GetTransform()->ApplyImpulse(Vector2f(float(jumpXDistance * direction), SPARKY_JUMP_HEIGHT));
			this->MoveTo(elapsedSec, m_TargetDirection.Normalized(), m_Speed);

			const Vector2f wallNormal{ this->GetCollisionBody()->GetFrontCollisionNormal() };
			const float wallToTargetDOT{ wallNormal.DotProduct(m_TargetDirection.Normalized()) };
			const bool facingWall{ wallToTargetDOT < 0 };

			if (this->GetCollisionBody()->IsWallbound() and facingWall) {
				m_TargetDirection *= -1; 
			}

			m_JumpClock = 0;
		};

		if (not airMovement) {
			m_JumpClock += elapsedSec;
		}
	}
}
