#include <iostream>
#include "pch.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Component.h"

AnimationController::AnimationController(Component* parent)
{ 
	SetParent(parent);
}

AnimationController::~AnimationController()
{
	for (size_t animationAtIndex{ 0 }; animationAtIndex < m_pAnimations.size(); ++animationAtIndex) {
		delete m_pAnimations[animationAtIndex];
		m_pAnimations[animationAtIndex] = nullptr;
	}
}

void AnimationController::DrawAnimations() const
{
	Animation* playingAnimation{ m_pAnimations[0] };
	if (playingAnimation!=nullptr) {
		if (!playingAnimation->IsEnded()) {
			playingAnimation->Draw();
		}
	}
}

void AnimationController::UpdateAnimations(float elapsedSec)
{
	for (Animation* animation : m_pAnimations) {
		if (!animation->IsEnded()) {
			animation->Update(elapsedSec);
		}
	};

	// FIND A WAY TO CLEAN THE ANIMATIONS THAT ARE NOT IN USE ANYMORE :))))
}

void AnimationController::AddAnimation(Animation* animation)
{
	int priority{ static_cast<int>(animation->GetAnimationPriority()) };

	if (m_pAnimations.size() > 0) {
		for (Animation* animationAtIndex : m_pAnimations) {
			int priorityAtIndex{ static_cast<int>(animationAtIndex->GetAnimationPriority()) };

			if (priority >= priorityAtIndex) {
				std::vector<Animation*>::iterator it = std::find(m_pAnimations.begin(), m_pAnimations.end(), animationAtIndex);
				m_pAnimations.insert(it, animation);
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
			delete animationToDelete;
			//m_pAnimations[animationAtIndex] = nullptr;
			std::vector<Animation*>::iterator it = std::find(m_pAnimations.begin(), m_pAnimations.end(), animationToDelete);
			m_pAnimations.erase(it);
			std::cout << "Removed animation !" << std::endl;
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
