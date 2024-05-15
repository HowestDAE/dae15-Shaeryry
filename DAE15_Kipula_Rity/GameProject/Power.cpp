#include "pch.h"
#include "Power.h"
#include <iostream>

enum class PowerTypes {
	None,
	Beam
};

Power::Power(Entity* entity, const PowerTypes powerType) :
	m_PowerType{ powerType },
	m_ElapsedTime{ 0 },
	m_AbilityTime{ 0 },
	m_Active{ false }
{
	SetEntity(entity);
}

Power::Power(Entity* entity)
	: Power(entity,PowerTypes::None)
{
}

Power::~Power()
{
	std::cout << "deleted power !" << std::endl;
}

void Power::Update(float elapsedSec)
{
	m_ElapsedTime += elapsedSec; 
}

void Power::Draw() const
{
}

void Power::Use()
{
	//std::cout << "use ability !" << std::endl;
	if (not IsActive()) {
		SetActive(true);
	}
}

void Power::SetEntity(Entity* newEntity)
{
	m_pEntity = newEntity;
}
