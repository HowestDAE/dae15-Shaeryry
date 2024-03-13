#include "pch.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Entity.h"
#include "Transform.h"

Animation::Animation(AnimationController* animationController, const std::string& animationName, const int frames, const int animationPriorityIndex) :
	m_pAnimationController{ animationController },
	m_AnimationName{ animationName },
	m_EntityName{ (m_pAnimationController->GetParent()->GetName()) },
	m_Priority{ static_cast<AnimationPriority>(animationPriorityIndex) },

	m_AnimationClock{ 0 },
	m_FrameCount{ frames },
	m_CurrentFrame{ 0 },
	m_TimePerFrame{ .125 },
	m_IsPaused{ false },
	m_IsLooped{ false },
	m_HasEnded{ false }
{
	m_pTexture = new Texture(GetAnimationPath());
	SetParent(m_pAnimationController);
	//m_pAnimationController->AddAnimation(this);
}

Animation::~Animation()
{
	DeleteAnimation();
}

void Animation::Draw() const
{
	if (m_pTexture != nullptr) {
		float frameWidth{ static_cast<float>(m_pTexture->GetWidth() / m_FrameCount) };
		Rectf dstRect{
			m_pAnimationController->GetParent()->GetTransform()->GetPosition().x,
			m_pAnimationController->GetParent()->GetTransform()->GetPosition().y,
			40.f,
			40.f
		}; //INTRODUCE WITH TRANSFORM CLASS !!!

		Rectf srcRect{
			frameWidth * m_CurrentFrame,
			0,
			frameWidth,
			m_pTexture->GetHeight(),
		};
		m_pTexture->Draw(dstRect,srcRect);
		//std::cout << m_AnimationName << " : " << m_CurrentFrame << " : " << m_AnimationClock << std::endl;
	}

}

void Animation::Update(float elapsedSec)
{
	if (!IsPaused()) {
		int frame{ static_cast<int>(m_AnimationClock / m_TimePerFrame) };
		int currentFrame{ (frame % m_FrameCount) };

		//std::cout << m_AnimationName << " : " << animationSpeed << std::endl;// << " : " << m_AnimationClock << std::endl;

		m_CurrentFrame = currentFrame; 
		m_AnimationClock += elapsedSec;
		
		// Loop logic???
		if (!IsLooped()) {
			if (frame >= m_FrameCount) {
				DeleteAnimation();
				m_pAnimationController->RemoveAnimation(this);
			};
		}
		
	}
}

void Animation::DeleteAnimation()
{
	if (!IsEnded()) {
		m_HasEnded = true;
		// Delete Texture !
		delete m_pTexture;
	}
	
}

std::string Animation::GetAnimationPath() const
{
	return "Animations/" + m_EntityName + "/" + m_AnimationName + ".png";
}
