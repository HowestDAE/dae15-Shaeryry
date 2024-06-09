#include "pch.h"
#include "GameOver.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Game.h"
#include "SoundEffect.h"

GameOver::GameOver(Game* game, SceneManager* manager) :
	Scene(game, manager),
	m_EndedScreen{ false },
	m_Played{ false },
	m_pBackground{ nullptr }
{
}

void GameOver::Initialize(const std::string& worldName)
{
	if (not m_Initialized) {
		m_pBackground = m_pTextureManager->GetTexture("GameOver", "GUI/Base/GameOver.png");
		m_Initialized = true;
		m_SceneTime = 0;
	}
}

void GameOver::Update(float elapsedSec)
{
	if (not m_Played) {
		m_Played = true;
		m_pSoundManager->GetSound("GameOver")->Play(0);
	}

	if (m_SceneTime >= 8) {
		if (not m_Destroying) {
			this->Destroy();
			this->GetGame()->ResetPlayerData();
			this->GetSceneManager()->LoadScene("Vegetable Valley 1");
		}
	};

	if (m_Destroying) {
		m_SceneInactiveTime += elapsedSec;
	};

	m_SceneTime += elapsedSec;
} 

void GameOver::Draw() const
{
	if (m_Initialized) {
		const float width{ m_pBackground->GetWidth() };
		const float height{ m_pBackground->GetHeight() };
		const float widthScale{ m_pGame->GetViewPort().width/ width };
		const float heightScale{ m_pGame->GetViewPort().height / height };

		m_pBackground->Draw(
			Rectf(0, 0, width * widthScale, height * heightScale)
		);
	}
}
