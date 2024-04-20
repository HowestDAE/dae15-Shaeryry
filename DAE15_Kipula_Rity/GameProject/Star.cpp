#include "pch.h"
#include "Star.h"
#include "Animation.h"
#include "Transform.h"

Star::Star(const Vector2f& from,const Vector2f& to,const float duration) :
	Projectile("Star",duration,from,to)
{
	SetSpeed(STAR_SPEED);
	SetDamage(1);

	this->GetTransform()->SetWidth(STAR_WIDTH);
	this->GetTransform()->SetHeight(STAR_HEIGHT);
	this->GetTransform()->SetPosition( GetOrigin() - Vector2f(STAR_WIDTH / 2, STAR_HEIGHT / 2) );

	Animation* starAnimation{ GetController()->PlayAnimation("Star", 4, 0)};
	starAnimation->SetUpdateTime(STAR_ANIMATION_UPDATE);
	starAnimation->Loop(true);
	SetAnimation(starAnimation);
}

void Star::OnDestroy(bool collidedWall)
{
	Projectile::OnDestroy(collidedWall);
	GetAnimation()->DeleteAnimation();
	GetController()->PlayAnimation("Star_Explode", 3, 1);
}

