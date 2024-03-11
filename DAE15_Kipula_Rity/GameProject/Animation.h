#pragma once
#include <iostream>

enum class AnimationPriority {
	Core = 0
};

class Animation
{
public:
	Animation(const std::string& animationName, const std::string& entityName,const int animationPriorityIndex);
	void Update(float elapsedSec);
	std::string GetAnimationPath() const;
private:
	float m_AnimationClock;
	AnimationPriority m_Priority;
	std::string m_Name;
	std::string m_AnimationPath; 
	std::string m_EntityName;

	int m_AnimationWidth;
	int m_AnimationHeight;
};

