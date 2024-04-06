#pragma once
#include "pch.h"
#include <vector>

class Scene;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void Update(float elapsedSec);
	void DrawScenes(const Rectf& viewport) const;
	Scene* GetCurrentScene() const;
	void AddScene(Scene* newScene);
private:
	float transitionTime;
	std::vector<Scene*> m_Scenes;
};

