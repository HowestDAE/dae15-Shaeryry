#pragma once
#include <iostream>
#include <Texture.h>


enum class AnimationPriority {
	Core = 0
};
class AnimationController;
class AnimationFrame;
class Animation
{
public:
	Animation(AnimationController* animationController,const std::string& animationName, const int frames,const int animationPriorityIndex);
	~Animation();

	void Update(float elapsedSec);
	// GET METHODS
	AnimationPriority GetAnimationPriority() const { return m_Priority; };
	std::string GetAnimationPath() const;
	Texture* GetAnimationTexture() const { return m_pTexture; };
	AnimationController* GetController() const { return m_pAnimationController; };
	// STATE METHODS
	bool IsPaused() const { return m_IsPaused; };
private:
	bool m_IsPaused; 
	float m_AnimationClock;
	int m_FrameCount;
	Texture* m_pTexture;
	std::vector<AnimationFrame*> m_AnimationFrames;
	AnimationController* m_pAnimationController;
	AnimationPriority m_Priority;
	std::string m_AnimationName;
	std::string m_EntityName;
};

