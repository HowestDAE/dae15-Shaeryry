#pragma once
#include <list>

class Animation;
class AnimationController
{
public:
	AnimationController();
	void Update(float elapsedSec);
private:
	std::list<Animation*> m_pAnimations;
	//float m_RunningTime;
};

