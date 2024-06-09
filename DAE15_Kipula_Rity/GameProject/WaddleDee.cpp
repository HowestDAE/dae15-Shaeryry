#include "pch.h"
#include "WaddleDee.h"

WaddleDee::WaddleDee(EntityManager* entityManager, const Vector2f& origin) : 
	Enemy(entityManager, origin, "Waddle Dee")
{
	std::map<int, AnimationData> waddleDeeTracks{};
	waddleDeeTracks[static_cast<int>(EntityState::Run)] = AnimationData{ "Run",2,WADDLEDEE_ANIMATION_UPDATE,true };
	this->SetAnimationData(waddleDeeTracks); 

	SetPower(PowerTypes::None);
	m_Speed = WADDLEDEE_MOVEMENT_SPEED;
	m_Score = 200;
}