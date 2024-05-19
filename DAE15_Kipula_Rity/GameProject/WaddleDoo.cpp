#include "pch.h"
#include "Enemy.h"
#include "WaddleDoo.h"
#include "Transform.h"
#include "Beam.h"

WaddleDoo::WaddleDoo(EntityManager* entityManager, const Vector2f& origin) : 
	Enemy(entityManager, origin, "Waddle Doo")
{
	std::map<int, AnimationData> waddleDooTracks{}; 
	waddleDooTracks[static_cast<int>(EntityState::Run)] = AnimationData{ "Run",2,WADDLEDOO_ANIMATION_UPDATE,true };
	this->SetAnimationData(waddleDooTracks); 
	 
	m_Speed = WADDLEDOO_MOVEMENT_SPEED;
	SetPower( PowerTypes::Beam );
	this->GetTransform()->SetGravity(WADDLEDOO_GRAVITY);
} 

void WaddleDoo::Update(float elapsedSec)
{
	/*if (m_pPower->IsActive()) { 
		if (m_pCoreAnimation != nullptr) { 
			const float timeRatio{ (GetClock() / 0.5f) };
			const float sinOffset{ float(sin(2*M_PI * timeRatio)) };
			std::cout << sinOffset << std::endl;
			const float currentOffset{
				float(300 * abs(sinOffset)) 
			};
			m_pCoreAnimation->SetOffset(Vector2f(0,-currentOffset));
		}
	}
	else {
		m_pCoreAnimation->SetOffset(Vector2f(0, 0));
	}*/
	Enemy::Update(elapsedSec);
}


void WaddleDoo::SpecialAttack(Entity* target)
{
	if (CanUseSpecial()) {
		const int rng{ rand() % 2 };
		const Vector2f vectorToTarget{ GetDirectionVector(this, target) };
		const float distance{ vectorToTarget.Length() }; 

		switch (rng)
		{
			case 0:
				if (distance <= BEAM_MAX_RANGE*1.25f) {
					m_pPower->Use();
				}
				break;
			case 1:
				this->GetTransform()->ApplyImpulse(Vector2f(0, WADDLEDOO_JUMP_POWER));
				break;
			default:
				break;
		}

		Enemy::SpecialAttack(target);
	};
}
