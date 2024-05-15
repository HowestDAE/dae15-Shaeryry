#pragma once
#include "pch.h"
#include <iostream>

enum class PowerTypes {
	None,
	Beam,
};

class Entity;
class Power;
class PowerManager final
{
public:
	explicit PowerManager(Entity* entity);
	Power* CreatePower(PowerTypes typePower);
private:
	Entity* m_pEntity;
};

