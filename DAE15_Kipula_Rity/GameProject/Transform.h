#pragma once
#include "utils.h";

class Transform
{
public:
	Transform();
	//~Transform();
	void Update(float elapsedSec);

	void SetPosition(const Vector2f& newPosition) { m_Position = newPosition; };
	void SetRotation(const float newRotation) { m_Rotation = newRotation; };

	Vector2f GetPosition() const { return m_Position; };
	float GetRotation() const { return m_Rotation; };

private:
	Vector2f m_Position;
	float m_Rotation;
};

