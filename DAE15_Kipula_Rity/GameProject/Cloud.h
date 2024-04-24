#pragma once
#include "Projectile.h"

class Cloud final : public Projectile
{
public:
	explicit Cloud(const Vector2f& from, const Vector2f& to, const float duration);
	void OnDestroy(bool collidedWall) override;
};