#include "pch.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Entity.h"

Animation::Animation(AnimationController* animationController, const std::string& animationName, const int frames, const int animationPriorityIndex) :
	m_pAnimationController{ animationController },
	m_AnimationName{ animationName },
	m_EntityName{ (m_pAnimationController->GetParent()->GetName()) },
	m_Priority{ static_cast<AnimationPriority>(animationPriorityIndex) },

	m_AnimationClock{ 0 },
	m_FrameCount{ frames },
	m_IsPaused{ false }
{
	m_pTexture = new Texture(GetAnimationPath());
	m_pAnimationController->AddAnimation(this);
}

Animation::~Animation()
{
	// Delete Frames !
	// Delete Texture !
	if (m_pTexture != nullptr) {
		delete m_pTexture;
	}
}

void Animation::Update(float elapsedSec)
{
	if (!this->IsPaused()) {
		m_AnimationClock += elapsedSec;
	}
}

std::string Animation::GetAnimationPath() const
{
	return "Animations/" + m_EntityName + "/" + m_AnimationName + ".png";
}
