#include "pch.h"
#include "Animation.h"

Animation::Animation(const std::string& animationName, const std::string& entityName, const int animationPriorityIndex) :
	m_Name{ animationName },
	m_Priority{ static_cast<AnimationPriority>(animationPriorityIndex) },
	m_EntityName{ entityName }
{
	m_AnimationPath = this->GetAnimationPath();
}

void Animation::Update(float elapsedSec)
{
	m_AnimationClock += elapsedSec;
}

std::string Animation::GetAnimationPath() const
{
	return m_EntityName + "/" + m_Name + ".png";
}
