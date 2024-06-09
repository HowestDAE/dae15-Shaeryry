#include "pch.h"
#include <iostream>
#include "GameValues.h"
#include "GUI.h"
#include "Entity.h"
#include "Player.h"
#include "Game.h"
#include "Scene.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Power.h"

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
	const Player* m_Player{ m_pScene->GetPlayer() };
	const int amountHealth{ m_Player->GetHealth() };
	const int currentFrame{ int(m_HudClock / 0.5f) };
	const Rectf viewport{ m_pScene->GetGame()->GetViewPort() };
	const std::string basePath{ "GUI/Base/" };
	const std::string elementsPath{ "GUI/Elements/" };
	const std::string powerIcons{ "GUI/Powers/" };
	const std::string fontPath{ "Fonts/" };

	const Color4f BG_COLOR{ .95f,.83f,.64f ,1.f };
	const Color4f FONT_COLOR{ .32f,.11f,0.01f ,1.f };
	const float WIDTH{ 248 };
	const float HEIGHT{ 64 };

	const float SCORE_POSITION_X{ 72 };
	const float SCORE_POSITION_Y{ 23 };

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

	const float LIVES_TEXT_POSITION_X{ 208 };
	const float LIVES_TEXT_POSITION_Y{ 32 };

	glPushMatrix();
	glScalef( (viewport.width/ WIDTH), ( (GUI_HEIGHT + GUI_OFFSET) / HEIGHT), 0 );

	// Base UI

	const Texture* nameTagUI;
	const Texture* scoreTagUI;
	const Texture* baseUI;

	baseUI = m_pTextureManager->GetTexture("BaseNormal", basePath + "Base.png");
	baseUI->Draw(
		Rectf(viewport.left, viewport.bottom, baseUI->GetWidth(), baseUI->GetHeight())
	);

	nameTagUI = m_pTextureManager->GetTexture("NameTag", elementsPath + "KirbyText.png");
	nameTagUI->Draw(
		Rectf(NAMETAG_POSITION_X, NAMETAG_POSITION_Y, nameTagUI->GetWidth(), nameTagUI->GetHeight())
	);

	scoreTagUI = m_pTextureManager->GetTexture("ScoreTag", elementsPath + "ScoreText.png");
	scoreTagUI->Draw(
		Rectf(SCORETAG_POSITION_X, SCORETAG_POSITION_Y, scoreTagUI->GetWidth(), scoreTagUI->GetHeight())
	);  
	 
	// Power 

	const Power* playerPower{ m_Player->GetPower() };
	std::string currentPower{ "None" }; 
	
	if (playerPower != nullptr) {
		currentPower = playerPower->GetPowerName();
	};

	// Hurt

	if (m_Player->GetHitClock() <= INVINCIBILITY_TIME) {
		currentPower = "Hurt";
	}

	// Died

	if (m_Player->GetHealth() <= 0) {
		currentPower = "Miss";
	};


	const Texture* PowerIcon;
	PowerIcon = m_pTextureManager->GetTexture(currentPower, powerIcons + currentPower + ".png");
	PowerIcon->Draw(
		Rectf(POWER_POSITION_X, POWER_POSITION_Y, PowerIcon->GetWidth(), PowerIcon->GetHeight())
	);

	// Lives

	const std::string kirbyLives{ std::to_string(m_pScene->GetGame()->GetPlayerData().lives) };
	const Texture* kirbyIcon;
	kirbyIcon = m_pTextureManager->GetTexture("KirbyIcon", elementsPath + "KirbyIcon.png");
	
	const int kirbyIconFrames{ 4 };
	const int kirbyAnimationFrame{ currentFrame % kirbyIconFrames };
	const float frameWidth{ (kirbyIcon->GetWidth() / kirbyIconFrames) };

	kirbyIcon->Draw(
		Rectf(KIRBY_POSITION_X, KIRBY_POSITION_Y, frameWidth, kirbyIcon->GetHeight()),
		Rectf(frameWidth * kirbyAnimationFrame, 0, frameWidth, kirbyIcon->GetHeight())
	);
	
	utils::SetColor(BG_COLOR);
	utils::FillRect(Rectf(LIVES_TEXT_POSITION_X, LIVES_TEXT_POSITION_Y, float(8 * 2), 8.f));

	const Texture* livesText{ new Texture("0" + kirbyLives, fontPath + "Kirbys-Adventure.ttf",8,FONT_COLOR) };
	livesText->Draw(
		Rectf(LIVES_TEXT_POSITION_X, LIVES_TEXT_POSITION_Y, livesText->GetWidth(), livesText->GetHeight())
	);

	// Health 

	utils::SetColor(BG_COLOR);
	utils::FillRect(Rectf(HP_POSITION_X, HP_POSITION_Y, float(8 * 6), 14.f));

	for (int healthPointIndex{ 0 }; healthPointIndex < KIRBY_MAX_HEALTH; healthPointIndex++) {
		const Texture* healthBarPoint;
		int healthFrames{ 2 };

		if (healthPointIndex < amountHealth) {
			healthBarPoint = m_pTextureManager->GetTexture("HP", elementsPath + "Health.png");
		}
		else {
			healthBarPoint = m_pTextureManager->GetTexture("HP_Lost", elementsPath + "HealthLost.png");
			healthFrames = 1;

		}

		const int kirbyAnimationFrame{ currentFrame % healthFrames };
		const float frameWidth{ (healthBarPoint->GetWidth() / healthFrames) };

		healthBarPoint->Draw(
			Rectf(HP_POSITION_X + ((healthBarPoint->GetWidth() / healthFrames) * healthPointIndex), HP_POSITION_Y, frameWidth, healthBarPoint->GetHeight()),
			Rectf(frameWidth * kirbyAnimationFrame, 0, frameWidth, healthBarPoint->GetHeight())
		);
	}

	// Score text
	std::string zeroes{ "" };
	const int amountNumbers{ 7 };
	const int scoreAmount{ m_pScene->GetGame()->GetPlayerData().score };

	for (size_t zeroIndex{}; zeroIndex < (amountNumbers - std::to_string(scoreAmount).size()); zeroIndex++) {
		zeroes += "0";
	};
	const Texture* scoreText{ new Texture(zeroes + std::to_string(scoreAmount), fontPath + "Kirbys-Adventure.ttf",8,FONT_COLOR) };

	utils::SetColor(BG_COLOR);
	utils::FillRect(Rectf(SCORE_POSITION_X, SCORE_POSITION_Y, float(8 * amountNumbers), livesText->GetHeight()));

	utils::SetColor(FONT_COLOR);

	scoreText->Draw(
		Rectf(SCORE_POSITION_X,SCORE_POSITION_Y, scoreText->GetWidth(), scoreText->GetHeight())
	);

	delete livesText;
	delete scoreText;
	glPopMatrix();

}
 