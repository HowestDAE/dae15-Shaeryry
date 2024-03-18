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
}

void Camera::Reset()
{
	glPopMatrix();
}

void Camera::DrawCamera(World* world, const Vector2f& center)
{
	glPushMatrix();

	/*Rectf worldRect{ m_pWorld->GetWorldSize() };
	Vector2f cameraPosition{};
	Vector2f playerPosition{ m_Player->GetTransform()->GetPosition() };
	cameraPosition.x = std::max( std::min( (worldRect.left - playerPosition.x) , 0.f) );
	*/
	Rectf worldRect{ world->GetWorldSize() };
	Vector2f aimPosition{ center };
	Vector2f cameraPosition{};

	float xPos{ (worldRect.left - aimPosition.x)  };
	float minCameraX{ std::min(xPos + (m_Viewport.width / 2) ,0.f) };
	float maxCameraX{ std::max( -(worldRect.width - m_Viewport.width) ,xPos) };

	cameraPosition.x = maxCameraX;

	glTranslatef(cameraPosition.x, cameraPosition.y, 0);
	
	std::cout << cameraPosition.x << std::endl;
}

