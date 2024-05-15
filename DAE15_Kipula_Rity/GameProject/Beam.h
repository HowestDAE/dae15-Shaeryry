#pragma once
#include "Power.h"
#include "pch.h"
#include "utils.h"
#include "Texture.h"
#include <vector>

class Animation;
class Entity;
class Beam final: public Power
{
public:
	explicit Beam(Entity* entity); 
	Beam& operator=(const Beam& rhs) = delete;
	Beam(const Beam& other) = delete;
	~Beam();
	virtual void Update(float elapsedSec) override; 
	virtual void Draw() const override;
	virtual void Use() override;
private:
	Animation* m_BeamAnimation;
	std::vector<Texture*> m_Stars;
	std::vector<Vector2f> m_Points;
	float m_AbilityClock;
	float m_TotalAngle;
	float m_StartAngle;
	int m_MaxSegments;
};

