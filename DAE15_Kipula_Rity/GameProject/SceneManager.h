#pragma once
#include "pch.h"
#include <vector>

class Game;
class Scene;
class SceneManager final {
public:
	explicit SceneManager(Game* game);
	SceneManager& operator=(const Scene& rhs) = delete;
	SceneManager(const Scene& other) = delete;
	~SceneManager();
	void Update(float elapsedSec);
	void DrawScenes(const Rectf& viewport) const;
	Scene* GetCurrentScene() const;
	Scene* GetPreviousScene() const;

	void CleanScenes();
	void LoadScene(Scene* newScene);
	void LoadScene(const std::string& worldName);
private:
	float RoundedTransition(const float input, const float transitionTime) const;
	void DrawBrightness(const float brightness) const;

	std::vector<Scene*> m_Scenes;
	Game* m_pGame;
};

