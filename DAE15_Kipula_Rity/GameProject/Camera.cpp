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

void Camera::DrawCamera(World* world, const Vector2f& center)
{
	glPushMatrix();

	Rectf worldRect{ world->GetWorldRect() };
	Vector2f aimPosition{ center };
	Vector2f cameraPosition{};

	float xPos{ (worldRect.left - aimPosition.x)  };
	float minEdge{ 0 };
	float maxEdge{ (worldRect.width * world->GetWorldScale()) - m_Viewport.width };

	float minCameraX{ std::min(xPos + (m_Viewport.width / 2),minEdge) };
	float maxCameraX{ std::max(-maxEdge ,xPos) };
	cameraPosition.x = std::max(minCameraX,maxCameraX);

	glTranslatef(cameraPosition.x, cameraPosition.y, 0);
}

