#pragma once
#include <utils.h>
#include "Component.h"

class World;
class Camera : public Component
{
public:
	Camera(const Rectf& viewport);
	~Camera();
	void Reset();
	void DrawCamera(World* world,const Vector2f& center);
private:
	Rectf m_Viewport;
};

