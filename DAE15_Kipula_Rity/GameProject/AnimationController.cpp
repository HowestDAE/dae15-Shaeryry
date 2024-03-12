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
	for (Animation* animation : m_pAnimations) {
		delete animation;
	};
}

void AnimationController::Update(float elapsedSec)
{
	//m_RunningTime += elapsedSec;
}

void AnimationController::AddAnimation(Animation* animation)
{
	int priority{ static_cast<int>(animation->GetAnimationPriority()) };

	if (m_pAnimations.size() > 0) {
		for (Animation* animationAtIndex : m_pAnimations) {
			int priorityAtIndex{ static_cast<int>(animationAtIndex->GetAnimationPriority()) };

			if (priority >= priorityAtIndex) {
				auto it = std::find(m_pAnimations.begin(), m_pAnimations.end(), animationAtIndex);
				m_pAnimations.insert(it, animation);
				break;
			}
		}
	} else {
		m_pAnimations.push_back(animation);
	}
}
