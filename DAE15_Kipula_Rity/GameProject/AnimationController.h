#pragma once
#include "pch.h"
#include <list>
#include "Component.h"
#include "vector"

class TextureManager;
class Entity;
class Animation;
class AnimationController : public Component
{
public:
	AnimationController(Component* parent);
	~AnimationController();;
	void DrawAnimations() const;
	void UpdateAnimations(float elapsedSec);
	void AddAnimation(Animation* animation);
	void RemoveAnimation(Animation* animation);
	Animation* PlayAnimation(const std::string& animationName, const int frames, const int animationPriorityIndex);
private:
	std::vector<Animation*> m_pAnimations;
	TextureManager* m_pTextureManager;
};

