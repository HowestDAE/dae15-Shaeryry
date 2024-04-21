#pragma once
#include "Projectile.h"

class Star final : public Projectile
{
public:
	explicit Star(const Vector2f& from, const Vector2f& to, const float duration);
	void OnDestroy(bool collidedWall) override;
};