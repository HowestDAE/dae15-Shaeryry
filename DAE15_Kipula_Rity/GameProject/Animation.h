#pragma once
#include "pch.h"
#include "utils.h"
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
	bool pingpong;
};

class AnimationController;
class Animation final : public Component {
public:
	explicit Animation(AnimationController* animationController,const std::string& animationName, const int frames,const int animationPriorityIndex);
	Animation& operator=(const Animation& rhs) = delete;
	Animation(const Animation& other) = delete;
	~Animation();

	virtual void Update(float elapsedSec);
	virtual void Draw() const; // draw animation

	void Loop(bool loopState) { m_Looped = loopState; };
	void SetUpdateTime(float updateTime) { m_TimePerFrame = updateTime; }
	void SetFlipped(bool state) { m_Flipped = state; };
	void SetPingPong(bool pingpong) { m_PingPong = pingpong; }
	void SetOffset(const Vector2f newOffset) { m_Offset = newOffset; }; 
	void SetWidth(float width) { m_Width = width; };
	void SetHeight(float height) { m_Height = height; };
	void SetAnimationRectDynamic(bool newState) { m_DynamicAnimationBox = newState; };

	void DeleteAnimation();
	// GET METHODS
	float GetWidth() const { return m_Width; };
	float GetHeight() const { return m_Height; };
	float GetAnimationUpdateTime() const { return m_TimePerFrame; }
	Vector2f GetAnimationOffset() const { return m_Offset; };
	AnimationPriority GetAnimationPriority() const { return m_Priority; }; 
	std::string GetAnimationPath() const;
	Texture* GetAnimationTexture() const { return m_pTexture; };
	AnimationController* GetController() const { return m_pAnimationController; };
	
	// STATE METHODS
	bool IsAnimationRectDynamic() const { return m_DynamicAnimationBox; };
	bool IsPaused() const { return m_Paused; };
	bool IsLooped() const { return m_Looped; };
	bool IsEnded() const { return m_HasEnded; };
	bool IsFlipped() const { return m_Flipped; };
	bool IsPingPong() const { return m_PingPong; };
	
private:
	bool m_DynamicAnimationBox;
	bool m_PingPong;
	bool m_HasEnded;
	bool m_Paused;
	bool m_Looped; 
	bool m_Flipped;
	float m_Width;
	float m_Height;
	float m_AnimationClock;
	float m_TimePerFrame;
	int m_FrameCount; 
	int m_CurrentFrame;
	Vector2f m_Offset;
	Texture* m_pTexture;
	AnimationController* m_pAnimationController;
	AnimationPriority m_Priority;
	std::string m_AnimationName;
	std::string m_EntityName;
};

