#pragma once
#include <vector>

class Transform;
class Component;
class CollisionHandler;
class CollisionBody
{
public: 
	CollisionBody(Component* Instance);
	void DrawCollider() const;
	void UpdateCollider(float elapsedSec);
	void ApplyDefaultCollisions();
	bool FrontCollision(const Vector2f& pos);

	void SetVertices(const std::vector<Point2f>& newVertices);
	void SetCollisionHandler(CollisionHandler* handler) { m_pCollisionHandler = handler; };
	utils::HitInfo CheckCollision(const Vector2f& from, const Vector2f& target);

	Component* GetComponent() const { return m_Instance; };
	std::vector<Point2f> GetVertices() const { return m_Vertices; };

	bool IsGrounded() const { return m_IsGrounded; };
	bool IsActive() const { return m_Active; };
private:
	CollisionHandler* m_pCollisionHandler;
	Component* m_Instance;
	std::vector<Point2f> m_Vertices;
	bool m_Active;
	bool m_IsGrounded;
};

