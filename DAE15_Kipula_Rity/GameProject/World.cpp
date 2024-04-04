#include "pch.h"
#include <Matrix2x3.h>
#include "World.h"
#include "TextureManager.h"
#include <SVGParser.h>
#include "Component.h"
#include "CollisionBody.h"

World::World(const WorldData& worldData,TextureManager* textureManager) :
	m_WorldScale{worldData.scale}
{

	SetName(worldData.name);
	SetTextureManager(textureManager);
	m_pWorldTexture = GetTextureManager()->GetTexture(worldData.name, GetWorldTexturePath());
	m_WorldRect = Rectf{	
		0,
		0,
		m_pWorldTexture->GetWidth(),
		m_pWorldTexture->GetHeight()
	};
	
	// COLLISION DATA SETUP
	const std::string collisionPath{ "Worlds/" + worldData.name + ".svg" };
	Matrix2x3 transform_matrix{
		Matrix2x3::CreateTranslationMatrix(0,0) *
		Matrix2x3::CreateRotationMatrix(0) *
		Matrix2x3::CreateScalingMatrix(Vector2f(m_WorldScale,m_WorldScale))
	};

	SVGParser::GetVerticesFromSvgFile(collisionPath, m_CollisionData);

	for (size_t index{}; index < m_CollisionData.size(); index++) {
		m_CollisionData[index] = transform_matrix.Transform(m_CollisionData[index]);
	};
	//

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

	//this->GetCollisionBody()->DrawCollider();
	//utils::DrawPolygon(m_CollisionData[0], true, 5.f);
}

void World::Update(float elapsedSec)
{
	if (this->GetCollisionBody() != nullptr) {
		this->GetCollisionBody()->SetVertices(m_CollisionData[0]);
	}
}

std::string World::GetWorldTexturePath()
{
	return "Worlds/" + m_Name + ".png";
}
