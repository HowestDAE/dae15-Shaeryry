#pragma once
#include "pch.h"
#include <vector>
#include <iostream>

class Transform;
class Component;
class CollisionHandler;

class CollisionBody final {
public: 
	explicit CollisionBody(Component* Instance);
	CollisionBody& operator=(const CollisionBody& rhs) = delete;
	CollisionBody(const CollisionBody& other) = delete;
	~CollisionBody();

	void DrawCollider() const;
	void UpdateCollider(float elapsedSec);
	void ApplyDefaultCollisions();
	 
	void SetTag(const std::string& tag) { m_Tag = tag; };
	void SetVertices(const std::vector<Point2f>& newVertices);
	void SetCollisionHandler(CollisionHandler* handler) { m_pCollisionHandler = handler; };
	utils::HitInfo CheckCollision(const Vector2f& from, const Vector2f& target,const std::vector<std::string>& tags={});

	std::string GetTag() const { return m_Tag; };
	Component* GetComponent() const { return m_Instance; }; 
	std::vector<Point2f> GetVertices() const { return m_Vertices; };
	Rectf GetRect() const;

	Vector2f GetFrontCollisionNormal() const { return m_FrontCollision.normal; };
	Vector2f GetGroundCollisionNormal() const { return m_FloorCollision.normal; };

	bool IsGrounded() const { return m_IsGrounded; };
	bool IsWallbound() const { return m_IsWallbound; };
	bool IsActive() const { return m_Active; }; 
private:
	CollisionHandler* m_pCollisionHandler;
	Component* m_Instance;
	std::vector<Point2f> m_Vertices;
	std::string m_Tag;
	utils::HitInfo m_FrontCollision;
	utils::HitInfo m_FloorCollision;
	bool m_Active;
	bool m_IsGrounded;
	bool m_IsWallbound;
};

