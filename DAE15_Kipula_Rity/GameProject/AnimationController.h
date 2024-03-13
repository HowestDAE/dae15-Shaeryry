#pragma once
#include <list>
#include "Component.h"
#include "vector"

class Animation;
class Entity;
class AnimationController : public Component
{
public:
	AnimationController(Component* parent);
	~AnimationController();
	void DrawAnimations() const;
	void UpdateAnimations(float elapsedSec);
	void AddAnimation(Animation* animation);
	void RemoveAnimation(Animation* animation);
	Animation* PlayAnimation(const std::string& animationName, const int frames, const int animationPriorityIndex);
private:
	std::vector<Animation*> m_pAnimations;
};

