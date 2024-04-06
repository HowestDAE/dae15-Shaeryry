#pragma once
#include "pch.h"
#include <iostream>

class Transform;
class TextureManager;
class CollisionBody;
class Component
{
public:
	Component(); 
	~Component();

	void SetName(const std::string& name) { m_Name = name; };
	std::string GetName() const { return m_Name; };

	void SetParent(Component* parent) { m_pParent = parent; };
	Component* GetParent() const { return m_pParent; }; 

	void SetTextureManager(TextureManager* textureManager) { m_pTextureManager = textureManager; };
	TextureManager* GetTextureManager() const { return m_pTextureManager; };

	Transform* GetTransform() const { return m_pTransform; };

	CollisionBody* GetCollisionBody() const { return m_pCollisionBody; };
	void SetCollisionBody(CollisionBody* body) { m_pCollisionBody = body; };
protected:
	std::string m_Name;
	Component* m_pParent; 
private:
	TextureManager* m_pTextureManager;
	Transform* m_pTransform;
	CollisionBody* m_pCollisionBody;
};

