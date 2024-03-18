#pragma once
#include <utils.h>
#include <Texture.h>
#include "Component.h"

class Camera;
class World : public Component
{
public:
	World(const std::string& worldName,TextureManager* textureManager);
	~World();
	void Draw() const;
	void SetWorldScale(float scale) { m_WorldScale = scale; }
	Rectf GetWorldSize() { return m_WorldRect; };
private:
	std::string GetWorldTexturePath();

	Texture* m_pWorldTexture;
	Rectf m_WorldRect;

	float m_WorldScale;
};

