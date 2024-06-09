#include "pch.h"
#include "EndScreen.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Game.h"
#include "Texture.h"
#include "SoundEffect.h"

EndScreen::EndScreen(Game* game, SceneManager* manager) :
	Scene(game, manager),
	m_EndedScreen{ false },
	m_Played{ false },
	m_pLogo{ nullptr },
	m_Text{  "Thank you for playing !!", "Fonts/Kirbys-Adventure.ttf", 16, Color4f(1, 1, 1, 1) }
{
	m_SceneTransitionTime = 1;
}

 
void EndScreen::Initialize(const std::string& worldName)
{
	if (not m_Initialized) {
		m_pLogo = m_pTextureManager->GetTexture("Logo", "GUI/Base/Logo.png");
		//m_Text = Texture("ho", "Fonts/Kirbys-Adventure.ttf", 8, Color4f(1,1,1,1));
		m_Initialized = true; 
		m_SceneTime = 0;
	}
}

void EndScreen::Update(float elapsedSec)
{
	if (IsReady()) {
		if (m_SceneTime >= 0.5f) {
			if (not m_Played) {
				m_Played = true;
				m_pSceneManager->StopMusic();
				m_pSoundManager->GetSound("Victory")->Play(0);
			}
		}
	}

	if (m_Destroying) {
		m_SceneInactiveTime += elapsedSec;
	};

	m_SceneTime += elapsedSec;

}

void EndScreen::Draw() const
{
	if (m_Initialized) {
		const float width{ m_pLogo->GetWidth() *.5f};
		const float height{ m_pLogo->GetHeight() *.5f };

		const float centerScreenX{ (m_pGame->GetViewPort().width / 2) };
		const float centerScreenY{ (m_pGame->GetViewPort().height / 2) };

		const float LOGO_OFFSET{ 50.f };
		const float TEXT_OFFSET{ -100.f };

		m_pLogo->Draw(
			Rectf(centerScreenX - (width / 2), centerScreenY - (height / 2) + LOGO_OFFSET, width, height)
		);

		m_Text.Draw( 
			Rectf(centerScreenX - m_Text.GetWidth() / 2, centerScreenY - (m_Text.GetHeight() / 2) + TEXT_OFFSET, 0, 0)
		);
	}
}
 