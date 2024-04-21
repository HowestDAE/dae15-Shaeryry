#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "CollisionBody.h"

Component::Component() :
	m_pParent{ nullptr },
	m_pTextureManager{ nullptr },
	m_pTransform{ new Transform() },
	m_pCollisionBody{ nullptr },
	m_Displacement(0,0),
	m_ShakingForce(0,0)
{
}

Component::~Component()
{
	if (m_pCollisionBody != nullptr) {
		delete m_pCollisionBody;
	}
	delete m_pTransform;
}

void Component::Update(float elapsedSec)
{
	// Shaking
	m_ShakingForce *= 0.98f;
}

void Component::ApplyComponentEffects() const
{
	glPushMatrix();
	Vector2f displacement{ m_Displacement };

	// Shaking
	if (m_ShakingForce.Length() > 2) {
		const int xForce{ int(m_ShakingForce.x) };
		const int yForce{ int(m_ShakingForce.y) };
		const int x{ (rand() % xForce) - (xForce / 2) };
		const int y{ (rand() % yForce) - (yForce / 2) };
		const float shakingX{ float(x) };
		const float shakingY{ float(y) };

		const Vector2f shakingMotion{ shakingX,shakingY };
		displacement += shakingMotion;
	}
	//

	glTranslatef(displacement.x, displacement.y, 0);
}

void Component::ShakeComponent(const Vector2f force, float intensity)
{
	m_ShakingForce = (force * intensity);
}

void Component::ResetEffectLayer() const
{
	glPopMatrix();
}
