#pragma once
#include "pch.h"

class Entity;
class Power
{
public:
	explicit Power(Entity* entity,const PowerTypes powerType);
	explicit Power(Entity* entity); 
	Power& operator=(const Power& rhs) = delete;
	Power(const Power& other) = delete;
	Power(Power&& other) = delete;
	Power& operator=(Power&& other) = delete;
	virtual ~Power();

	virtual void Update(float elapsedSec);
	virtual void Draw() const;
	virtual void Use();

	void SetActive(bool newState) { m_Active = newState; };
	void SetEntity(Entity* newEntity);
	bool IsActive() const { return m_Active; }; 

	PowerTypes GetType() const { return m_PowerType; };
	std::string GetPowerName() const { return m_PowerName; };
	Entity* GetEntity() const { return m_pEntity; };
protected:
	std::string m_PowerName;
	bool m_Active;
	float m_AbilityTime;
private:
	Entity* m_pEntity;
	PowerTypes m_PowerType;
	float m_ElapsedTime;
};

