#include "pch.h"
#include "Camera.h"
#include "World.h"
#include <iostream>
#include <algorithm>

Camera::Camera(const Rectf& viewport):
	m_Viewport{viewport}
{
}

Camera::~Camera()
{
	Reset();
}

void Camera::Reset()
{
	glPopMatrix();
}

void Camera::UpdateCamera(float elapsedSec, World* world, const Vector2f& center)
{
	Rectf worldRect{ world->GetWorldRect() };
	Vector2f aimPosition{ center };
	Vector2f cameraPosition{};

	float xPos{ (worldRect.left - aimPosition.x) };
	float minEdge{ 0 };
	float maxEdge{ (worldRect.width * world->GetWorldScale()) - m_Viewport.width };

	float minCameraX{ std::min(xPos + (m_Viewport.width / 2),minEdge) };
	float maxCameraX{ std::max(-maxEdge ,xPos) };
	cameraPosition.x = std::max(minCameraX, maxCameraX);

	m_CameraViewport.left = cameraPosition.x;
	m_CameraViewport.bottom = cameraPosition.y;
	m_CameraViewport.width = m_Viewport.width;
	m_CameraViewport.height = m_Viewport.height;

}

void Camera::DrawCamera() const
{
	glPushMatrix();

	glTranslatef(m_CameraViewport.left, m_CameraViewport.bottom, 0);
}

bool Camera::IsPointOnScreen(const Point2f& point) const
{
	Rectf m_CurrentViewport{ GetCameraViewport() };
	m_CurrentViewport.left = -m_CurrentViewport.left;

	return (
		point.x > m_CurrentViewport.left && point.x < m_CurrentViewport.left + m_CurrentViewport.width
		&& point.y > m_CurrentViewport.bottom && point.y < m_CurrentViewport.bottom + m_CurrentViewport.height
	);
}


