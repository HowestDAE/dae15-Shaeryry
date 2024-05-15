#include "pch.h"
#include <iostream>
#include "Power.h"
#include "Beam.h"
#include "Entity.h"
#include "Transform.h"
#include "EntityManager.h"
#include "AnimationController.h"

Beam::Beam(Entity* entity) :
	Power(entity,PowerTypes::Beam),
	m_AbilityClock{ 0 },
	m_BeamAnimation{ nullptr }
{
	m_PowerName = "Beam";
	m_AbilityTime = BEAM_LENGTH;
	m_TotalAngle = BEAM_TOTAL_ANGLE;
	m_StartAngle = BEAM_START_ANGLE;
	m_MaxSegments = BEAM_MAX_SEGMENTS;
	
	for (int indexStar{ 0 }; indexStar < m_MaxSegments; indexStar++) {
		m_Stars.push_back( new Texture("Props/BeamStar.png") );
	}
 }

Beam::~Beam()
{ 
	for (size_t starTextureIndex{ 0 }; starTextureIndex < m_Stars.size(); starTextureIndex++) {
		delete m_Stars[starTextureIndex];
	}
}

void Beam::Update(float elapsedSec)
{
	if (IsActive()) { 
		m_AbilityClock += elapsedSec;	

		const float orientation{ GetEntity()->GetTransform()->GetLookDirection() };
		const float timePeriod{ (m_AbilityClock / m_AbilityTime) };
		const float currentAngle{ m_StartAngle - (m_TotalAngle * timePeriod) };
		const float angleInRad{ currentAngle * float(M_PI / 180) };
		const float totalRange{ BEAM_MAX_RANGE };
		const float range{ float(totalRange/m_MaxSegments) };

		const Vector2f beamVector{
			cos(angleInRad) * orientation, 
			sin(angleInRad)
		}; 

		for (int indexParticle{ 0 }; indexParticle < m_MaxSegments; indexParticle++) {
			const Vector2f starVector{ GetEntity()->GetTransform()->GetCenterPosition() + beamVector.Normalized() * (range + (range * indexParticle)) };

			if (m_Points.size() <= indexParticle) {
				m_Points.push_back(starVector);
			}
			else {
				m_Points[indexParticle] = starVector;
			}

			const std::vector<Entity*> targets{ 
				GetEntity()->GetManager()->CastHitbox(GetEntity(), Rectf(starVector.x - (BEAM_STAR_SIZE / 2) , starVector.y - (BEAM_STAR_SIZE / 2), BEAM_STAR_HITBOX_SIZE, BEAM_STAR_HITBOX_SIZE))
			};
			for (size_t targetIndex{ 0 }; targetIndex < targets.size(); targetIndex++) {
				targets[targetIndex]->TakeDamage(1);
			}
		};

		if (m_AbilityClock > m_AbilityTime) { 
			SetActive(false);
		}
	}
	else {
		if (m_BeamAnimation!=nullptr) {
			m_BeamAnimation->DeleteAnimation();
			m_BeamAnimation = nullptr;
		}
	};

	Power::Update(elapsedSec);
}

void Beam::Draw() const
{
	if (IsActive()) {
		for (size_t starTextureIndex{ 0 }; starTextureIndex < m_Stars.size(); starTextureIndex++) {
			const Rectf starLocation{
				m_Points[starTextureIndex].x - (BEAM_STAR_SIZE / 2),
				m_Points[starTextureIndex].y - (BEAM_STAR_SIZE / 2),
				BEAM_STAR_SIZE,
				BEAM_STAR_SIZE
			};

			m_Stars[starTextureIndex]->Draw(starLocation);
		}
	}
}

void Beam::Use()
{
	if (not IsActive()) {
		m_AbilityClock = 0;
		Power::Use();

		m_BeamAnimation = GetEntity()->GetAnimator()->PlayAnimation("Beam", 2, 3);
		m_BeamAnimation->Loop(true);
		m_BeamAnimation->SetUpdateTime(BEAM_ANIMATION_UPDATE);
		m_BeamAnimation->SetAnimationRectDynamic(false);
		m_BeamAnimation->SetWidth(DEFAULT_ENTITY_WIDTH * float(m_BeamAnimation->GetWidth()/16.f));
		m_BeamAnimation->SetHeight(DEFAULT_ENTITY_HEIGHT);

	}
}
