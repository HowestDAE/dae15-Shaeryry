#pragma once
#include "pch.h"
#include "utils.h"

class Transform final {
public:
	explicit Transform();
	//~Transform();

	void Update(float elapsedSec); 
	void ApplyPhysics(float elapsedSec);

	void SetGravity(float gravity) { m_Gravity = gravity; };
	// Position

	void SetPosition(const Vector2f& newPosition) { m_Position = newPosition; };
	Vector2f GetPosition() const { return m_Position; };
	Vector2f GetCenterPosition() const;
	// Velocity 

	void AddVelocity(const Vector2f& Velocity) { m_Velocity += Velocity; };
	void ApplyImpulse(const Vector2f& Velocity) { m_Impulse += Velocity; };
	void SetVelocity(const Vector2f& newVelocity) { m_Velocity = newVelocity; };

	//Width & Height
	void SetWidth(float width) { m_Width = width; };
	void SetHeight(float height) { m_Height = height; };
	float GetLookDirection() const { return m_LookDirection; };


	//Acceleration & Deceleration

	void AddAcceleration(float accel);
	void SetAcceleration(float accel) { m_Acceleration = accel; };
	void SetDeceleration(float decel) { m_Deceleration = decel; }
	float GetAcceleration() const { return m_Acceleration; };

	//Rotation & Orientation
	void SetFlipped(bool flipped); 

	Vector2f GetVelocity() const { return m_Velocity; };
	Vector2f GetCurrentVelocity() const { return m_CurrentVelocity; };
	float GetWidth() const { return m_Width; };
	float GetHeight() const { return m_Height; };
private:
	void SetCurrentVelocity(const Vector2f& newVelocity) { m_CurrentVelocity = newVelocity; };
	Vector2f m_CurrentVelocity;
	Vector2f m_Position;
	Vector2f m_Impulse;
	Vector2f m_Velocity;
	Vector2f m_PreviousPosition; 
	float m_Gravity;
	float m_Width;
	float m_Height;
	float m_Acceleration;
	float m_Deceleration;
	float m_LookDirection;
	//float m_Rotation;
};

