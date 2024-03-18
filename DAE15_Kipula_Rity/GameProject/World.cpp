#include "pch.h"
#include "World.h"
#include "TextureManager.h"
#include "Component.h"

World::World(const std::string& worldName,TextureManager* textureManager) :
	m_WorldScale{1}
{
	SetName(worldName);
	SetTextureManager(textureManager);
	m_pWorldTexture = GetTextureManager()->GetTexture(worldName, GetWorldTexturePath());
	m_WorldRect = Rectf{	
		0,
		0,
		m_pWorldTexture->GetWidth(),
		m_pWorldTexture->GetHeight()
	};
	
}

World::~World()
{

}

void World::Draw() const
{
	glPushMatrix();
	glScalef(m_WorldScale, m_WorldScale, m_WorldScale);

	if (m_pWorldTexture != nullptr) {
		m_pWorldTexture->Draw(m_WorldRect);
	};

	glPopMatrix();
}

std::string World::GetWorldTexturePath()
{
	return "Worlds/" + m_Name + ".png";
}
