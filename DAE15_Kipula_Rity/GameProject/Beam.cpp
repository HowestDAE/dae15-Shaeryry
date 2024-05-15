#include "pch.h"
#include <iostream>
#include "Power.h"
#include "Beam.h"
#include "Entity.h"
#include "Transform.h"
#include "EntityManager.h"

Beam::Beam(Entity* entity) :
	Power(entity,PowerTypes::Beam),
	m_AbilityClock{ 0 }
{
	m_PowerName = "Beam";
	m_AbilityTime = 1;
	m_TotalAngle = 60;
	m_StartAngle = 30;
	m_MaxSegments = 5;
}

Beam::~Beam()
{
	std::cout << "beam destroyed !!" << std::endl; 
}

void Beam::Update(float elapsedSec)
{
	if (IsActive()) { 
		m_AbilityClock += elapsedSec;	

		const float orientation{ GetEntity()->GetTransform()->GetLookDirection() };
		const float timePeriod{ (m_AbilityClock / m_AbilityTime) };
		const float currentAngle{ m_StartAngle - (m_TotalAngle * timePeriod) };
		const float angleInRad{ currentAngle * float(M_PI / 180) };
		const float totalRange{ 50 };
		const float range{ float(totalRange/m_MaxSegments) };

		const Vector2f beamVector{
			cos(angleInRad) * orientation, 
			sin(angleInRad)
		}; 

		for (int indexParticle{ 0 }; indexParticle < m_MaxSegments; indexParticle++) {
			const Vector2f starVector{ GetEntity()->GetTransform()->GetCenterPosition() + beamVector.Normalized() * (range * indexParticle) };

			if (m_Points.size() <= indexParticle) {
				m_Points.push_back(starVector);
			} else {
				m_Points[indexParticle] = starVector;
			}
		};

		if (m_AbilityClock > m_AbilityTime) { 
			SetActive(false);
		}
	};

	Power::Update(elapsedSec);
}

void Beam::Draw() const
{
	if (IsActive()) {
			 
	}
}

void Beam::Use()
{
	if (not IsActive()) {
		m_AbilityClock = 0;
		Power::Use();
	}
}
