#pragma once
#include "pch.h"
#include <iostream>
#include "Component.h"
#include <Texture.h>
#include <vector>

enum class AnimationPriority {
	Core = 0,
	Movement = 1,
	Action = 2,
	Action1 = 3,
};

struct AnimationData {
	std::string name; 
	int frames;
	float updateTime;
	bool loop;
	int priority = 0;
};

class AnimationController;
class Animation final : public Component {
public:
	explicit Animation(AnimationController* animationController,const std::string& animationName, const int frames,const int animationPriorityIndex);
	Animation& operator=(const Animation& rhs) = delete;
	Animation(const Animation& other) = delete;
	~Animation();

	void Draw() const; // draw animation
	void Update(float elapsedSec);

	void Loop(bool loopState) { m_Looped = loopState; };
	void SetUpdateTime(float updateTime) { m_TimePerFrame = updateTime; }
	void SetFlipped(bool state) { m_Flipped = state; }

	void DeleteAnimation();
	// GET METHODS
	AnimationPriority GetAnimationPriority() const { return m_Priority; }; 
	std::string GetAnimationPath() const;
	Texture* GetAnimationTexture() const { return m_pTexture; };
	AnimationController* GetController() const { return m_pAnimationController; };
	// STATE METHODS
	bool IsPaused() const { return m_Paused; };
	bool IsLooped() const { return m_Looped; };
	bool IsEnded() const { return m_HasEnded; };
	bool IsFlipped() const { return m_Flipped; };
private:
	bool m_HasEnded;
	bool m_Paused;
	bool m_Looped; 
	bool m_Flipped;
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

