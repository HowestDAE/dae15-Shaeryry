#include "pch.h"
#include "HotHead.h"

HotHead::HotHead(EntityManager* entityManager, const Vector2f& origin) : 
	Enemy(entityManager, origin, "Hot Head")
{
	std::map<int, AnimationData> hotHeadTracks{};
	hotHeadTracks[static_cast<int>(EntityState::Run)] = AnimationData{ "Run",2,HOT_HEAD_ANIMATION_UPDATE,true };
	this->SetAnimationData(hotHeadTracks);

	SetPower(PowerTypes::None);
	m_Speed = HOT_HEAD_MOVEMENT_SPEED;
	m_Score = 200;
}
 