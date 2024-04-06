#include "pch.h"
#include "Transform.h"
#include <iostream>

Transform::Transform() :
	m_Position(0, 0),
	m_PreviousPosition(0, 0),
	m_Velocity(0, 0),
	m_CurrentVelocity(0, 0),
	m_Width{ 0 },
	m_Height{ 0 },
	m_Acceleration{0},
	m_Deceleration{ DEFAULT_ENTITY_DECELERATION },
	m_LookDirection{1}
{
}

void Transform::Update(float elapsedSec)
{
	const float Deceleration{ m_Deceleration * elapsedSec };

	m_Position += (m_Velocity * elapsedSec);

	// Deceleration

	AddAcceleration(-Deceleration);

	// Velocity

	const Vector2f currentVelocity{ (m_Position - m_PreviousPosition) };
	SetCurrentVelocity(currentVelocity); // UPDATE THE VELOCITY !!

	// Update Position Tracker

	if (m_Position != m_PreviousPosition) {
		m_PreviousPosition = m_Position;
	};

}

void Transform::ApplyPhysics(float elapsedSec)
{
	AddVelocity(Vector2f{ 0,-GRAVITY }*elapsedSec);	
}

void Transform::AddAcceleration(float accel)
{
	m_Acceleration += accel;
	if (m_Acceleration > 100) {
		m_Acceleration = 100;
	}
	else if (m_Acceleration < 0) {
		m_Acceleration = 0;
	}
}

void Transform::SetFlipped(bool flipped)
{
	if (flipped) {
		m_LookDirection = -1;
	}
	else {
		m_LookDirection = 1;
	}
}
