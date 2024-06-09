#pragma once
#include "pch.h"
#include "utils.h"
#include "Component.h"
#include "AnimationController.h"


class Projectile : public Component
{
public:
	explicit Projectile(const std::string& projectileName,float duration,const Vector2f& from, const Vector2f& to);
	Projectile& operator=(const Projectile& rhs) = delete;
	Projectile(const Projectile& other) = delete;
	Projectile(Projectile&& other) = delete;
	Projectile& operator=(Projectile&& other) = delete;
	~Projectile();

	void SetSpeed(float speed) { m_Speed = speed; };
	void SetDamage(int damage) { m_Damage = damage; };
	void SetAnimation(Animation* animation) { m_Animation = animation; };
	void Destroy(float duration=0, bool collidedWall = false);

	virtual void Update(float elapsedSec);
	virtual void Draw() const; 
	virtual void OnDestroy(bool collidedWall); 

	bool CanDelete() const;
	bool IsActive() const { return m_Active; };

	int GetDamage() const { return m_Damage; };
	Vector2f GetOrigin() const { return m_Origin; };
	AnimationController* GetController() const { return m_pAnimationController; };
	Animation* GetAnimation() const { return m_Animation; }
private:
	AnimationController* m_pAnimationController;
	Animation* m_Animation;
	// clocks
	float m_ElapsedTime;
	float m_DeleteElapsedTime;

	// variables
	float m_DelayedRemoval;
	bool m_Active;

	// Projectile Attributes
	Vector2f m_Origin;
	Vector2f m_Target;
	float m_Speed;
	float m_Duration;
	int m_Damage;
};

