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
	void UpdateCamera(float elapsedSec, World* world, const Vector2f& center);
	void DrawCamera() const;
	Rectf GetCameraViewport() const { return m_CameraViewport; };
	bool IsPointOnScreen(const Point2f& point) const;
private:
	Rectf m_CameraViewport;
	Rectf m_Viewport;
};

