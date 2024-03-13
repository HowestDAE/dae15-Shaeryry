#pragma once
#include <iostream>

class Transform;

class Component
{
public:
	Component(); 
	~Component();
	void SetName(const std::string& name) { m_Name = name; };
	std::string GetName() const { return m_Name; };

	void SetParent(Component* parent) { m_pParent = parent; };
	Component* GetParent() const { return m_pParent; };

	Transform* GetTransform() const { return m_pTransform; };
protected:
	std::string m_Name;
	Component* m_pParent; 
private:
	Transform* m_pTransform;
};

