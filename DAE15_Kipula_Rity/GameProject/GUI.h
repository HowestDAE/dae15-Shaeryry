#pragma once
#include "pch.h"

class Scene;
class TextureManager;
class GUI final
{
public:
	explicit GUI(Scene* scene);
	GUI(const GUI& other) = delete;
	GUI& operator=(const GUI& other) = delete;
	GUI(GUI&& other) = delete;
	GUI& operator=(GUI&& other) = delete;
	~GUI();
	void Update(float elapsedSec);
	void Draw() const;
private:
	float m_HudClock;
	Scene* m_pScene;
	TextureManager* m_pTextureManager;
};

