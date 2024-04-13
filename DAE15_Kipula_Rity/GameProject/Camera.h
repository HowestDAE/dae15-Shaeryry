#pragma once
#include "pch.h"
#include <utils.h>
#include "Component.h"

class World;
class Camera final : public Component
{
public:
	explicit Camera(const Rectf& viewport);
	Camera& operator=(const Camera& rhs) = delete;
	Camera(const Camera& other) = delete;
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

