#pragma once
#include "pch.h"
#include <vector>

class Scene;
class SceneManager final {
public:
	explicit SceneManager();
	SceneManager& operator=(const Scene& rhs) = delete;
	SceneManager(const Scene& other) = delete;
	~SceneManager();
	void Update(float elapsedSec);
	void DrawScenes(const Rectf& viewport) const;
	Scene* GetCurrentScene() const;
	void AddScene(Scene* newScene);
private:
	float transitionTime;
	std::vector<Scene*> m_Scenes;
};

