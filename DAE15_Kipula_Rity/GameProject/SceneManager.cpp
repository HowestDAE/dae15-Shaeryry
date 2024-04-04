#include "pch.h"
#include <utils.h>
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() :
	transitionTime{ 3 }
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
	for (size_t sceneIndex{}; sceneIndex < m_Scenes.size(); sceneIndex++) {
		m_Scenes[sceneIndex]->Update(elapsedSec);
	};
}

void SceneManager::DrawScenes(const Rectf& viewport) const
{
	if (m_Scenes.size() > 0) {
		Scene* ActiveScene{ GetCurrentScene() };
		ActiveScene->Draw();
	}
}

Scene* SceneManager::GetCurrentScene() const
{
	return m_Scenes[m_Scenes.size()-1];
}

void SceneManager::AddScene(Scene* newScene)
{
	//GetCurrentScene()->SetPause(true);
	m_Scenes.push_back(newScene);
}	
