#pragma once
#include <list>
#include "Component.h"

class Animation;
class Entity;
class AnimationController : public Component
{
public:
	AnimationController(Component* parent);
	~AnimationController();
	void Update(float elapsedSec);
	void AddAnimation(Animation* animation);
private:
	std::list<Animation*> m_pAnimations;
	//float m_RunningTime;
};

