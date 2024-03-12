#pragma once
#include <Texture.h>
#include "Component.h"

class Animation;
class AnimationFrame : public Component
{
public:
	AnimationFrame(Animation* animation,Texture* animationTexture, int frameIdx);
	~AnimationFrame();
private:
	Animation* m_pAnimation;
	Rectf m_SpriteRect;
};

