#pragma once
#include <iostream>
#include "Component.h"
#include <Texture.h>
#include <vector>

enum class AnimationPriority {
	Core = 0,
	Movement = 1,
	Action = 2
};

struct AnimationData {
	std::string name; 
	int frames;
	float updateTime;
	bool loop;
};

class AnimationController;
class Animation : public Component
{
public:
	Animation(AnimationController* animationController,const std::string& animationName, const int frames,const int animationPriorityIndex);
	~Animation();
	void Draw() const; // draw animation
	void Update(float elapsedSec);

	void Loop(bool loopState) { m_IsLooped = loopState; };
	void SetUpdateTime(float updateTime) { m_TimePerFrame = updateTime; }

	void DeleteAnimation();
	// GET METHODS
	AnimationPriority GetAnimationPriority() const { return m_Priority; }; 
	std::string GetAnimationPath() const;
	Texture* GetAnimationTexture() const { return m_pTexture; };
	AnimationController* GetController() const { return m_pAnimationController; };
	// STATE METHODS
	bool IsPaused() const { return m_IsPaused; };
	bool IsLooped() const { return m_IsLooped; };
	bool IsEnded() const { return m_HasEnded; };
	static const float DEFAULT_ANIMATION_UPDATE;
private:
	bool m_HasEnded;
	bool m_IsPaused;
	bool m_IsLooped;
	float m_AnimationClock;
	float m_TimePerFrame;
	int m_FrameCount; 
	int m_CurrentFrame;
	Texture* m_pTexture;
	AnimationController* m_pAnimationController;
	AnimationPriority m_Priority;
	std::string m_AnimationName;
	std::string m_EntityName;
};

