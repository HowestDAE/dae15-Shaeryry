#pragma once
#include "Scene.h"

class Texture;
class Game;
class GameOver final : public Scene
{
public:
	explicit GameOver(Game* game, SceneManager* manager);

	virtual void Initialize(const std::string& worldName) override;
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
private:
	bool m_Played;
	bool m_EndedScreen;
	Texture* m_pBackground;
};

 