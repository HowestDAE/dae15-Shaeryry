#pragma once
#include <vector>
#include <iostream>

class Transform;
class Component;
class CollisionHandler;
class CollisionBody
{
public: 
	CollisionBody(Component* Instance);
	~CollisionBody();
	void DrawCollider() const;
	void UpdateCollider(float elapsedSec);
	void ApplyDefaultCollisions();
	bool FrontCollision(const Vector2f& pos);
	 
	void SetTag(const std::string& tag) { m_Tag = tag; };
	void SetVertices(const std::vector<Point2f>& newVertices);
	void SetCollisionHandler(CollisionHandler* handler) { m_pCollisionHandler = handler; };
	utils::HitInfo CheckCollision(const Vector2f& from, const Vector2f& target,const std::vector<std::string>& tags={});

	std::string GetTag() const { return m_Tag; };
	Component* GetComponent() const { return m_Instance; }; 
	std::vector<Point2f> GetVertices() const { return m_Vertices; };

	bool IsGrounded() const { return m_IsGrounded; };
	bool IsWallbound() const { return m_IsWallbound; };
	bool IsActive() const { return m_Active; }; 
private:
	CollisionHandler* m_pCollisionHandler;
	Component* m_Instance;
	std::vector<Point2f> m_Vertices;
	std::string m_Tag;
	bool m_Active;
	bool m_IsGrounded;
	bool m_IsWallbound;
};

