#include "pch.h"
#include "Enemy.h"
#include "WaddleDoo.h"
#include "Transform.h"
#include "Beam.h"

WaddleDoo::WaddleDoo(EntityManager* entityManager, const Vector2f& origin) : 
	Enemy(entityManager, origin, "Waddle Doo"),
	m_SavedDirection{false},
	m_WaddleDooTargetDirection{0,0}
{
	std::map<int, AnimationData> waddleDooTracks{}; 
	waddleDooTracks[static_cast<int>(EntityState::Run)] = AnimationData{ "Run",2,WADDLEDOO_ANIMATION_UPDATE,true };
	this->SetAnimationData(waddleDooTracks);

	SetPower( PowerTypes::Beam );
}

void WaddleDoo::GoToTarget(float elapsedSec, Entity* target)
{
	if (!m_SavedDirection) {
		m_WaddleDooTargetDirection = GetDirectionVector(this, target) * 5;
		m_SavedDirection = true;
	};

	this->SetState(EntityState::Run);
	this->MoveTo(elapsedSec,m_WaddleDooTargetDirection.Normalized(), WADDLEDOO_MOVEMENT_SPEED);
	//std::cout << "Waddle doo ting innit" << std::endl;
}
 