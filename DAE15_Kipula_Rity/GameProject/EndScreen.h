#pragma once
#include "Scene.h"
#include "Texture.h"

class Texture;
class Game;
class EndScreen final : public Scene
{
public:
	explicit EndScreen(Game* game, SceneManager* manager);

	virtual void Initialize(const std::string& worldName) override;
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
private:
	bool m_Played;
	bool m_EndedScreen;
	Texture* m_pLogo;
	Texture m_Text;
};


