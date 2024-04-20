#pragma once

enum class PowerTypes {
	None,
};

class Power
{
public:
	explicit Power(const PowerTypes powerType);
	explicit Power();
private:
	PowerTypes m_PowerType;
};

