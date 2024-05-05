#include "pch.h"
#include <Matrix2x3.h>
#include "World.h"
#include "TextureManager.h"
#include <SVGParser.h>
#include "Component.h"
#include "CollisionBody.h"

World::World(const WorldData& worldData, TextureManager* textureManager) :
	m_Data{ worldData },
	m_WorldScale{worldData.scale},
	m_Doors{ worldData.doors },
	m_WorldElapsedTime{0}
{

	SetName(worldData.name);
	SetTextureManager(textureManager);
	m_pWorldTexture = GetTextureManager()->GetTexture(worldData.name, GetWorldTexturePath());
	m_WorldRect = Rectf{	
		0,
		0,
		m_pWorldTexture->GetWidth(),
		m_pWorldTexture->GetHeight() / m_Data.frames
	};
	
	// COLLISION SETUP

	const std::string collisionPath{ "Worlds/" + worldData.name + ".svg" };
	const std::string pathformPath{ "Worlds/" + worldData.name + "_Platforms" + ".svg"};

	Matrix2x3 transform_matrix{
		Matrix2x3::CreateTranslationMatrix(0,0) *
		Matrix2x3::CreateRotationMatrix(0) *
		Matrix2x3::CreateScalingMatrix(Vector2f(m_WorldScale,m_WorldScale))
	};

	SVGParser::GetVerticesFromSvgFile(collisionPath, m_CollisionData);
	SVGParser::GetVerticesFromSvgFile(pathformPath, m_PlatformsData);

	//std::cout << m_CollisionData.size() << std::endl;

	// World
	for (size_t index{}; index < m_CollisionData.size(); index++) {
		m_CollisionData[index] = transform_matrix.Transform(m_CollisionData[index]);
	}

	// Platforms

	for (size_t platformIndex{}; platformIndex < m_PlatformsData.size(); platformIndex++) {
		m_PlatformsData[platformIndex] = transform_matrix.Transform(m_PlatformsData[platformIndex]);
	};

	// PLATFORMS

}

World::~World()
{
	for (size_t bodyIndex{}; bodyIndex < m_Bodies.size(); bodyIndex++) {
		delete m_Bodies[bodyIndex];
	};

	for (size_t platformIndex{}; platformIndex < m_Platforms.size(); platformIndex++) {
		delete m_Platforms[platformIndex];
	}
}

void World::Draw() const
{
	glPushMatrix();	
	glScalef(m_WorldScale, m_WorldScale, m_WorldScale);

	if (m_pWorldTexture != nullptr) {
		const int frame{ int(m_WorldElapsedTime / m_Data.updateFrames) };
		const int currentFrame{ frame % m_Data.frames };
		const Rectf srcRect{
			0,
			currentFrame * m_WorldRect.height,
			m_WorldRect.width,
			m_WorldRect.height
		};
		m_pWorldTexture->Draw(m_WorldRect, srcRect);
	};

	glPopMatrix();

	/*utils::SetColor(Color4f(1, 0.5, 1, 1));
	for (size_t index{}; index < m_CollisionData.size(); index++) {
		utils::DrawPolygon(m_CollisionData[index], true, 5.f);
	};

	for (size_t indexPlatform{}; indexPlatform < m_Platforms.size(); indexPlatform++) {
		utils::DrawPolygon(m_Platforms[indexPlatform], true, 5.f);
	};*/

	for (size_t doorIndex{}; doorIndex < m_Doors.size(); doorIndex++) {
		utils::SetColor(Color4f(1, 1, 1, 1));
		utils::FillRect(m_Doors[doorIndex].area);
	}
}

void World::Update(float elapsedSec)
{
	m_WorldElapsedTime += elapsedSec;
}

void World::CreateCollisions(CollisionHandler* collisionHandler)
{
	for (size_t verticesDataIndex{}; verticesDataIndex < m_CollisionData.size(); verticesDataIndex++) {
		CollisionBody* newBody{ new CollisionBody(this) };
		newBody->SetVertices(m_CollisionData[verticesDataIndex]);
		newBody->SetTag("Collidable");
		m_Bodies.push_back(newBody);
		collisionHandler->AddBody(newBody);
	};

	for (size_t platformVerticesDataIndex{}; platformVerticesDataIndex < m_PlatformsData.size(); platformVerticesDataIndex++) {
		CollisionBody* newPlatformBody{ new CollisionBody(this) };
		newPlatformBody->SetVertices(m_PlatformsData[platformVerticesDataIndex]);
		newPlatformBody->SetTag("Collidable");
		m_Platforms.push_back(newPlatformBody);
		collisionHandler->AddBody(newPlatformBody);
	}

	this->SetCollisionBody(nullptr);
}
 
std::string World::GetWorldTexturePath()
{
	return "Worlds/" + m_Name + ".png";
}
