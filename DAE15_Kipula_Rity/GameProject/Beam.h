#pragma once
#include "Power.h"
#include "pch.h"
#include "utils.h"
#include <vector>

class Entity;
class Beam final: public Power
{
public:
	explicit Beam(Entity* entity); 
	~Beam();
	virtual void Update(float elapsedSec) override; 
	virtual void Draw() const override;
	virtual void Use() override;
private:
	std::vector<Vector2f> m_Points; 
	float m_AbilityClock;
	float m_TotalAngle;
	float m_StartAngle;
	int m_MaxSegments;
};

