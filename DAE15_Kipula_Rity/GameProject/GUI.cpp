#include "pch.h"
#include "GameValues.h"
#include "GUI.h"
#include "Entity.h"
#include "Player.h"
#include "Game.h"
#include "Scene.h"
#include "Texture.h"
#include "TextureManager.h"

GUI::GUI(Scene* scene):
	m_pScene{ scene },
	m_HudClock{0}
{
	m_pTextureManager = new TextureManager();
}

GUI::~GUI()
{
	delete m_pTextureManager;
}

void GUI::Update(float elapsedSec)
{
	m_HudClock += elapsedSec;
}

void GUI::Draw() const
{
	// Variables
	const int amountHealth{ m_pScene->GetPlayer()->GetHealth() };
	const int currentFrame{ int(m_HudClock / 0.5f) };
	const Rectf viewport{ m_pScene->GetGame()->GetViewPort() };
	const std::string basePath{ "GUI/Base" };
	const std::string elementsPath{ "GUI/Elements" };
	const std::string powerIcons{ "GUI/Powers" };

	const float WIDTH{ 248 };
	const float HEIGHT{ 64 };

	const float HP_POSITION_X{ 72 };
	const float HP_POSITION_Y{ 37 };

	const float KIRBY_POSITION_X{ 187 };
	const float KIRBY_POSITION_Y{ 32 };

	const float NAMETAG_POSITION_X{ 15 };
	const float NAMETAG_POSITION_Y{ 39 };

	const float SCORETAG_POSITION_X{ 15 };
	const float SCORETAG_POSITION_Y{ 23 };


	const float POWER_POSITION_X{ 144 };
	const float POWER_POSITION_Y{ 16 };

	glPushMatrix();
	glScalef( (viewport.width/ WIDTH), ( (GUI_HEIGHT + GUI_OFFSET) / HEIGHT), 0 );

	// Base UI

	const Texture* nameTagUI;
	const Texture* scoreTagUI;
	const Texture* baseUI;

	baseUI = m_pTextureManager->GetTexture("BaseNormal", basePath + "/Base.png");
	baseUI->Draw(
		Rectf(viewport.left, viewport.bottom, baseUI->GetWidth(), baseUI->GetHeight())
	);

	nameTagUI = m_pTextureManager->GetTexture("NameTag", elementsPath + "/KirbyText.png");
	nameTagUI->Draw(
		Rectf(NAMETAG_POSITION_X, NAMETAG_POSITION_Y, nameTagUI->GetWidth(), nameTagUI->GetHeight())
	);

	scoreTagUI = m_pTextureManager->GetTexture("ScoreTag", elementsPath + "/ScoreText.png");
	scoreTagUI->Draw(
		Rectf(SCORETAG_POSITION_X, SCORETAG_POSITION_Y, scoreTagUI->GetWidth(), scoreTagUI->GetHeight())
	);

	// Power

	const std::string currentPower{ "Normal" };
	const Texture* PowerIcon;
	PowerIcon = m_pTextureManager->GetTexture("PowerSlot", powerIcons + "/" + currentPower + ".png");
	PowerIcon->Draw(
		Rectf(POWER_POSITION_X, POWER_POSITION_Y, PowerIcon->GetWidth(), PowerIcon->GetHeight())
	);

	// Lives

	const Texture* kirbyIcon;
	kirbyIcon = m_pTextureManager->GetTexture("KirbyIcon", elementsPath + "/KirbyIcon.png");
	
	const int kirbyIconFrames{ 4 };
	const int kirbyAnimationFrame{ currentFrame % kirbyIconFrames };
	const float frameWidth{ (kirbyIcon->GetWidth() / kirbyIconFrames) };

	kirbyIcon->Draw(
		Rectf(KIRBY_POSITION_X, KIRBY_POSITION_Y, frameWidth, kirbyIcon->GetHeight()),
		Rectf(frameWidth * kirbyAnimationFrame, 0, frameWidth, kirbyIcon->GetHeight())
	);

	// Health 

	for (int healthPointIndex{ 0 }; healthPointIndex < amountHealth; healthPointIndex++) {
		const Texture* healthBarPoint;
		healthBarPoint = m_pTextureManager->GetTexture("HP", elementsPath + "/Health.png");

		const int healthFrames{ 2 };
		const int kirbyAnimationFrame{ currentFrame % healthFrames };
		const float frameWidth{ (healthBarPoint->GetWidth() / healthFrames) };

		healthBarPoint->Draw(
			Rectf(HP_POSITION_X + ((healthBarPoint->GetWidth() / 2) * healthPointIndex), HP_POSITION_Y, frameWidth, healthBarPoint->GetHeight()),
			Rectf(frameWidth * kirbyAnimationFrame, 0, frameWidth, healthBarPoint->GetHeight())
		);
	}

	glPopMatrix();

}
