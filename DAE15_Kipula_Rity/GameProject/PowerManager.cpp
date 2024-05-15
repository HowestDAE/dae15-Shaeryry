#include "pch.h"
#include "PowerManager.h"
#include "Beam.h"


PowerManager::PowerManager(Entity* entity) :
	m_pEntity{ entity }
{
}

Power* PowerManager::CreatePower(PowerTypes typePower)
{
	Power* powerCreated;
	switch (typePower)
	{ 
		case PowerTypes::Beam:
			powerCreated = new Beam(m_pEntity);
			break;
		default:
			powerCreated = new Power(m_pEntity);
			break; 
	};

	return powerCreated;	
}
