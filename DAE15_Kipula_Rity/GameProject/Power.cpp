#include "pch.h"
#include "Power.h"

Power::Power(const PowerTypes powerType)
	: m_PowerType{powerType}
{
}

Power::Power()
	: Power(PowerTypes::None)
{
}
