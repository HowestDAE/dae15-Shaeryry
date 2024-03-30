#pragma once
#include "utils.h"

class Transform // convert to struct later????
{
public:
	Transform();
	//~Transform();

	void Update(float elapsedSec);
	void ApplyPhysics(float elapsedSec);

	// Position

	void SetPosition(const Vector2f& newPosition) { m_Position = newPosition; };
	Vector2f GetPosition() const { return m_Position; };
	// Velocity 

	void AddVelocity(const Vector2f& Velocity) { m_Velocity += Velocity; };
	void SetVelocity(const Vector2f& newVelocity) { m_Velocity = newVelocity; };

	//Width & Height
	void SetWidth(float width) { m_Width = width; };
	void SetHeight(float height) { m_Height = height; };
	float GetLookDirection() const { return m_LookDirection; };

	//Acceleration
	void AddAcceleration(float accel);
	void SetAcceleration(float accel) { m_Acceleration = accel; }
	float GetAcceleration() const { return m_Acceleration; };

	//Rotation & Orientation
	void SetFlipped(bool flipped); 

	Vector2f GetVelocity() const { return m_Velocity; };
	Vector2f GetCurrentVelocity() const { return m_CurrentVelocity; };
	float GetWidth() const { return m_Width; };
	float GetHeight() const { return m_Height; };

	static const float GRAVITY;
private:
	void SetCurrentVelocity(const Vector2f& newVelocity) { m_CurrentVelocity = newVelocity; };
	Vector2f m_CurrentVelocity;
	Vector2f m_Position;
	Vector2f m_Velocity;
	Vector2f m_PreviousPosition; 
	float m_Width;
	float m_Height;
	float m_Acceleration;
	float m_LookDirection;
	//float m_Rotation;
};

