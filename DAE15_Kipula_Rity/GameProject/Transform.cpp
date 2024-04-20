#include "pch.h"
#include "Transform.h"
#include <iostream>

Transform::Transform() :
	m_Position(0, 0),
	m_PreviousPosition(0, 0),
	m_Velocity(0, 0),
	m_Impulse(0,0),
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
	const float GravityFrameIndependant{ (GRAVITY * elapsedSec) };
	const float FakeAirPressureFrameIndependant{ (FAKE_AIR_PRESSURE * elapsedSec) };

	const float Deceleration{ m_Deceleration * elapsedSec };
	const Vector2f newVelocity{ (m_Velocity + m_Impulse) };

	m_Position += (newVelocity * elapsedSec);


	// Deceleration

	AddAcceleration(-Deceleration);

	// Velocity

	const Vector2f currentVelocity{ (m_Position - m_PreviousPosition) };
	SetCurrentVelocity(currentVelocity); // UPDATE THE VELOCITY !!

	// Impulse stuff

		// x
		if (m_Impulse.Length()> MINIMUM_IMPULSE_LENGTH){
			if (m_Impulse.x < 0) {
				m_Impulse.x += FakeAirPressureFrameIndependant;
			}
			else {
				m_Impulse.x -= FakeAirPressureFrameIndependant;
			}
			// y
			if (m_Impulse.y < 0) {
				m_Impulse.y += GravityFrameIndependant;
			}
			else {
				m_Impulse.y -= GravityFrameIndependant;
			}
		}
		else {
			m_Impulse = Vector2f();
		}
		

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
