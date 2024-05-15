#include "pch.h"
#include "Power.h"
#include <iostream>

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
