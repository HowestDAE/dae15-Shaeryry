#include "pch.h"
#include "Projectile.h"
#include "Transform.h"
#include "AnimationController.h"
#include "CollisionBody.h"


Projectile::Projectile(const std::string& projectileName, float duration, const Vector2f& from, const Vector2f& to) :
	m_Active{ true },
	m_ElapsedTime{ 0 },
	m_DeleteElapsedTime{ 0 },
	m_DelayedRemoval{0},
	m_Speed{0},
	m_Damage{0},
	m_Duration{ duration },
	m_Origin{ from },
	m_Target{ to }
{
	m_pAnimationController = new AnimationController(this);
	this->SetName("Projectile");
	this->GetTransform()->SetPosition(m_Origin);
	this->GetTransform()->SetWidth(PROJECTILE_DEFAULT_WIDTH);
	this->GetTransform()->SetHeight(PROJECTILE_DEFAULT_HEIGHT);
}

Projectile::~Projectile()
{
	delete m_pAnimationController;
}

void Projectile::Destroy(float duration, bool collidedWall)
{
	m_DelayedRemoval = duration;
	m_DeleteElapsedTime = 0;
	OnDestroy(collidedWall);
}

void Projectile::Update(float elapsedSec)
{
	const Transform* projectileTransform{ this->GetTransform() };

	if (m_Active) {
		const Vector2f originToTarget{ (m_Target - m_Origin) };
		const Vector2f displacement{ originToTarget.Normalized() * m_Speed * elapsedSec };
		this->GetTransform()->SetPosition(projectileTransform->GetPosition() + displacement);


		this->GetCollisionBody()->UpdateCollider(elapsedSec);
		const Vector2f origin{ projectileTransform->GetPosition() + Vector2f(projectileTransform->GetWidth() / 2,projectileTransform->GetHeight() / 2) };
		const Vector2f frontCheck{ origin + Vector2f(Vector2f((projectileTransform->GetWidth() / 2) * projectileTransform->GetLookDirection(),0)) };
		utils::HitInfo frontCollision{ this->GetCollisionBody()->CheckCollision(origin,frontCheck,{"Collidable"}) };
		if (frontCollision.lambda != -1) {
			Destroy(1,true);
		}
	}

	m_pAnimationController->UpdateAnimations(elapsedSec);
	if ( (m_ElapsedTime > m_Duration) and m_Active) {
		Destroy();
	};

	m_ElapsedTime += elapsedSec;
	if (not m_Active) {
		m_DeleteElapsedTime += elapsedSec;
	}

}

void Projectile::Draw() const
{
	m_pAnimationController->DrawAnimations();
}

void Projectile::OnDestroy(bool collidedWall)
{
	m_Active = false;
}

bool Projectile::CanDelete() const
{
	return
		not m_Active
		and(m_DeleteElapsedTime > m_DelayedRemoval);
}
