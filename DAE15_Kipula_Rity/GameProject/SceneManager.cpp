#include "pch.h"
#include <utils.h>
#include "SceneManager.h"
#include "Scene.h"
#include "Game.h"

SceneManager::SceneManager(Game* game) :
	m_pGame{game}
{
}

SceneManager::~SceneManager()
{
	for (size_t sceneIndex{}; sceneIndex < m_Scenes.size(); sceneIndex++) {
		delete m_Scenes[sceneIndex];
		m_Scenes[sceneIndex] = nullptr;
	}
}

void SceneManager::Update(float elapsedSec)
{
	const Scene* activeScene{ GetCurrentScene() };

	for (size_t sceneIndex{}; sceneIndex < m_Scenes.size(); sceneIndex++) {
		Scene* sceneAtIndex{ m_Scenes[sceneIndex] };
		sceneAtIndex->Update(elapsedSec);
	};
}

void SceneManager::DrawScenes(const Rectf& viewport) const
{
	const size_t amountScenes{ m_Scenes.size() };
	if (amountScenes > 0) {
		// Active Scene
		Scene* ActiveScene{ GetCurrentScene() };

		if (ActiveScene->IsReady()) {
			ActiveScene->Draw();
			
			const float transitionTime{ ActiveScene->GetTransitionTime() };
			const float inputTime{ ActiveScene->GetSceneTimer() - transitionTime - SCENE_INITIAL_DARKNESS };
			const float visibleTime{ RoundedTransition(inputTime,transitionTime) };
			DrawBrightness( (1 - visibleTime) );
		}
		else {
			// Previous Scene (this is to draw if the current scene isn't doing ready yet)
			if (amountScenes > 1) {
				Scene* PreviousScene{ GetPreviousScene() };
				if (PreviousScene != nullptr) {
					const float inactiveTime{ RoundedTransition(PreviousScene->GetSceneInactiveTimer(),ActiveScene->GetTransitionTime() ) };
					//std::cout << inactiveTime << std::endl;

					PreviousScene->Draw();
					DrawBrightness(inactiveTime);
				}
			}

		}

	}
}

Scene* SceneManager::GetCurrentScene() const
{
	return m_Scenes[m_Scenes.size()-1];
}

Scene* SceneManager::GetPreviousScene() const
{
	if (m_Scenes.size() > 1) {
		return m_Scenes[(m_Scenes.size() - 1)-1];
	}

	return nullptr;
}

void SceneManager::CleanScenes()
{
	for (size_t sceneIndex{}; sceneIndex < m_Scenes.size(); sceneIndex++) {
		if (m_Scenes.size() > MAX_SCENE_AMOUNT) {
			delete m_Scenes[sceneIndex];
			m_Scenes.erase(m_Scenes.begin() + sceneIndex);
		}
	};
}

void SceneManager::LoadScene(Scene* newScene)
{
	//GetCurrentScene()->SetPause(true);
	newScene->SetSceneManager(this);
	m_Scenes.push_back(newScene);
	CleanScenes();
}

void SceneManager::LoadScene(const std::string& worldName)
{
	Scene* newScene{ new Scene(m_pGame,this) };
	newScene->Initialize(worldName);
	LoadScene(newScene);
}

float SceneManager::RoundedTransition(const float input, const float transitionTime) const
{
	return std::ceil( (input / transitionTime) * 10.f ) / 10.f;
}

void SceneManager::DrawBrightness(const float brightness) const
{
	utils::SetColor(Color4f(0, 0, 0, brightness));
	//std::cout << brightness << std::endl;
	utils::FillRect(m_pGame->GetViewPort());
}

