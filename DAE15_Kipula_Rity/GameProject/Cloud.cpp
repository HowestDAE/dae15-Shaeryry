#include "pch.h"
#include "Cloud.h"
#include "Animation.h"
#include "Transform.h"

Cloud::Cloud(const Vector2f& from, const Vector2f& to, const float duration) :
	Projectile("Cloud", duration, from, to) 
{
	SetSpeed(CLOUD_SPEED);
	SetDamage(1);

	this->GetTransform()->SetWidth(CLOUD_WIDTH);
	this->GetTransform()->SetHeight(CLOUD_HEIGHT);
	this->GetTransform()->SetPosition(GetOrigin() - Vector2f(CLOUD_WIDTH / 2, CLOUD_HEIGHT / 2));

	Animation* cloudAnimation{ GetController()->PlayAnimation("Cloud", 1, 0) };
	cloudAnimation->SetUpdateTime(STAR_ANIMATION_UPDATE);
	cloudAnimation->Loop(true);
	SetAnimation(cloudAnimation);
}