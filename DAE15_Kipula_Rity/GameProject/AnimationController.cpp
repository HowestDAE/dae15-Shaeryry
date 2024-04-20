#include <iostream>
#include "pch.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Component.h"
#include "TextureManager.h"

AnimationController::AnimationController(Component* parent)
	: m_pAnimations{}
{ 
	m_pTextureManager = new TextureManager();
	SetParent(parent);
	SetTextureManager(m_pTextureManager);
}

AnimationController::~AnimationController()
{
	for (size_t animationAtIndex{ 0 }; animationAtIndex < m_pAnimations.size(); ++animationAtIndex) {
		delete m_pAnimations[animationAtIndex];
		m_pAnimations[animationAtIndex] = nullptr;
	}
	delete m_pTextureManager;
}


void AnimationController::DrawAnimations() const
{
	if (GetTextureManager() != nullptr) {

		if (m_pAnimations.size() > 0) {
			Animation* playingAnimation{ m_pAnimations[0] };
		//	std::cout << playingAnimation->GetName() << std::endl;
			if (playingAnimation != nullptr) {
				if (!playingAnimation->IsEnded()) {
					playingAnimation->Draw();
				}
			}
		}
	}
}

void AnimationController::UpdateAnimations(float elapsedSec)
{
	for (size_t animationAtIndex{ 0 }; animationAtIndex < m_pAnimations.size(); animationAtIndex++) {
		Animation* animation{ m_pAnimations.at(animationAtIndex) };
		if (!animation->IsEnded()) {
			animation->Update(elapsedSec);
		};
		// Post update
		if (animation->IsEnded()) {
			RemoveAnimation(animation);
			std::cout << "#Animations ->" << m_pAnimations.size() << std::endl;
		}
	}
}

void AnimationController::AddAnimation(Animation* animation)
{
	int priority{ static_cast<int>(animation->GetAnimationPriority()) };
	std::cout << "Animation added ! " << animation->GetName() << std::endl;

	if (m_pAnimations.size() > 0) {
		for (Animation* animationAtIndex : m_pAnimations) {
			int priorityAtIndex{ static_cast<int>(animationAtIndex->GetAnimationPriority()) };

			if (priority >= priorityAtIndex) {
				std::vector<Animation*>::iterator it = std::find(m_pAnimations.begin(), m_pAnimations.end(), animationAtIndex);
				m_pAnimations.insert(it, animation);
				//std::cout << "Added animation ! : " << animation->GetAnimationPath() << std::endl;
				break;
			}
		}
	} else {
		m_pAnimations.push_back(animation);
	}
}

void AnimationController::RemoveAnimation(Animation* animation)
{
	for (size_t animationAtIndex{ 0 }; animationAtIndex < m_pAnimations.size(); ++animationAtIndex) {
		if (m_pAnimations[animationAtIndex] == animation) {
			Animation* animationToDelete{ m_pAnimations[animationAtIndex] };
			std::cout << "Removed animation ! : " << animationToDelete->GetAnimationPath() << std::endl;
			delete animationToDelete;
			//m_pAnimations[animationAtIndex] = nullptr;
			std::vector<Animation*>::iterator it = std::find(m_pAnimations.begin(), m_pAnimations.end(), animationToDelete);
			m_pAnimations.erase(it);
		}
	};
}

Animation* AnimationController::PlayAnimation(const std::string& animationName, const int frames, const int animationPriorityIndex)
{
	Animation* newAnimation;
	newAnimation = new Animation(this, animationName, frames, animationPriorityIndex);
	if (newAnimation != nullptr) {
		AddAnimation(newAnimation);
	};

	return newAnimation;
}
