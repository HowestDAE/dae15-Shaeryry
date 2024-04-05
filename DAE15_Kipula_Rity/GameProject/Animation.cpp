#include "pch.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Entity.h"
#include "Transform.h"
#include "TextureManager.h"

const float Animation::DEFAULT_ANIMATION_UPDATE{.125};

Animation::Animation(AnimationController* animationController, const std::string& animationName, const int frames, const int animationPriorityIndex) :
	m_pAnimationController{ animationController },
	m_AnimationName{ animationName },
	m_EntityName{ (m_pAnimationController->GetParent()->GetName()) },
	m_Priority{ static_cast<AnimationPriority>(animationPriorityIndex) },

	m_AnimationClock{ 0 },
	m_FrameCount{ frames },
	m_CurrentFrame{ 0 },
	m_TimePerFrame{ DEFAULT_ANIMATION_UPDATE },
	m_IsPaused{ false },
	m_IsLooped{ false },
	m_HasEnded{ false }
{
	std::string animationKey{ m_EntityName + GetAnimationPath() };
	m_pTexture = m_pAnimationController->GetTextureManager()->GetTexture(animationKey,GetAnimationPath()); //new Texture(GetAnimationPath()); // USE TEXTURE MANAGER TO OPTIMIZE THIS LATER !!!
	SetParent(m_pAnimationController);
	SetName(animationName);
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

		const float frameWidth{ static_cast<float>(m_pTexture->GetWidth() / m_FrameCount) };
		const Vector2f position{ m_pAnimationController->GetParent()->GetTransform()->GetPosition() };
		const float width{ m_pAnimationController->GetParent()->GetTransform()->GetWidth() };
		const float height{ m_pAnimationController->GetParent()->GetTransform()->GetHeight() };
		const float lookDirection{ m_pAnimationController->GetParent()->GetTransform()->GetLookDirection() };

		glPushMatrix();
		glTranslatef(position.x - std::min(0.f,width*lookDirection), position.y, 0);
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
		//delete m_pTexture; // remove once texture manager
	}
	
}

std::string Animation::GetAnimationPath() const
{
	return "Animations/" + m_EntityName + "/" + m_AnimationName + ".png";
}
