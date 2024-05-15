#include "pch.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Entity.h"
#include "Transform.h"
#include "TextureManager.h"

Animation::Animation(AnimationController* animationController, const std::string& animationName, const int frames, const int animationPriorityIndex) :
	m_pAnimationController{ animationController },
	m_AnimationName{ animationName },
	m_EntityName{ (m_pAnimationController->GetParent()->GetName()) },
	m_Priority{ static_cast<AnimationPriority>(animationPriorityIndex) },
	m_Offset{ Vector2f(0,0) },
	m_CurrentFrame{ 0 },
	m_AnimationClock{ 0 },
	m_Width{ 0 },
	m_Height{ 0 },
	m_FrameCount{ frames },
	m_TimePerFrame{ DEFAULT_ANIMATION_UPDATE },
	m_DynamicAnimationBox{ true },
	m_PingPong{ false },
	m_Flipped{ false },
	m_Paused{ false },
	m_Looped{ false },
	m_HasEnded{ false }
{
	std::string animationKey{ m_EntityName + GetAnimationPath() };
	//std::cout << animationKey << std::endl;
	m_pTexture = m_pAnimationController->GetTextureManager()->GetTexture(animationKey,GetAnimationPath()); //new Texture(GetAnimationPath()); // USE TEXTURE MANAGER TO OPTIMIZE THIS LATER !!!
	SetParent(m_pAnimationController);
	SetName(animationName);
	m_Width = m_pTexture->GetWidth()/m_FrameCount;
	m_Height = m_pTexture->GetHeight();
	//std::cout << "Created animation > " << animationName << std::endl;
	//m_pAnimationController->AddAnimation(this);
}

Animation::~Animation()
{
	DeleteAnimation();
}

void Animation::Draw() const
{
	if (m_pTexture != nullptr) {
		float width{ m_Width };
		float height{ m_Height };

		if (m_DynamicAnimationBox) {
			width = m_pAnimationController->GetParent()->GetTransform()->GetWidth();
			height = m_pAnimationController->GetParent()->GetTransform()->GetHeight();
		};

		const float frameWidth{ static_cast<float>(m_pTexture->GetWidth() / m_FrameCount) };
		const Vector2f position{ m_pAnimationController->GetParent()->GetTransform()->GetPosition() };

		float lookDirection{ m_pAnimationController->GetParent()->GetTransform()->GetLookDirection() };
		
		if (m_Flipped) {
			lookDirection *= -1;
		};

		glPushMatrix();
		glTranslatef( (position.x + m_Offset.x) - std::min(0.f, width * lookDirection), position.y + m_Offset.y, 0);
		glScalef(lookDirection, 1, 1);
		Rectf dstRect{
			0,//m_pAnimationController->GetParent()->GetTransform()->GetPosition().x,
			0,//m_pAnimationController->GetParent()->GetTransform()->GetPosition().y,
			width,
			height
		}; 

		Rectf srcRect{
			(frameWidth * m_CurrentFrame), // Current Animation frame
			0, // 0 cuz animations are straight lines
			frameWidth, // Frame width of the animation
			m_pTexture->GetHeight(),
		};
		m_pTexture->Draw(dstRect,srcRect);

		glPopMatrix();
		//std::cout << m_AnimationName << " : " << m_CurrentFrame << " : " << m_AnimationClock << std::endl;
	}

}

void Animation::Update(float elapsedSec)
{
	if (!IsPaused()) {
		const float animationLength{ m_TimePerFrame * float(m_FrameCount) };
		int frame{ int(m_AnimationClock / m_TimePerFrame) };
		int currentFrame{ (frame % m_FrameCount) };

		if (!IsPingPong()) {
			m_CurrentFrame = currentFrame;
		}
		else {
			const float animationRatio{ m_AnimationClock / animationLength };
			const float fullPeriod{ float(M_PI) };
			const float periodAnimation{ fullPeriod * animationRatio };

			int pingpongFrame{ int(m_FrameCount * sin(periodAnimation)) };
			//std::cout << m_AnimationName << " : " << pingpongFrame << std::endl;// << " : " << m_AnimationClock << std::endl;
			m_CurrentFrame = abs(pingpongFrame);

		}
		m_AnimationClock += elapsedSec;
		
		// Loop logic???
		if (!IsLooped()) {
			if (frame >= m_FrameCount) {
				DeleteAnimation();
			};
		}
		
	}
}

void Animation::DeleteAnimation()
{
	if (!IsEnded()) {
		m_HasEnded = true;
	}
	
}

std::string Animation::GetAnimationPath() const
{
	return "Animations/" + m_EntityName + "/" + m_AnimationName + ".png";
}
