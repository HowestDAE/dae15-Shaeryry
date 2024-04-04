#pragma once
#include <iostream>
#include "Component.h"

class Camera;
class World;
class EntityManager;
class TextureManager;
class CollisionHandler;
class Game;
class Player;
class Scene
{
public:
	Scene(Game* game);
	~Scene();
	void Initialize(const std::string& worldName);
	void Update(float elapsedSec);
	void Draw() const;
	void SetPause(bool paused) { m_Paused = paused; };
	float GetSceneTimer() const { return m_SceneTime; }
	Player* GetPlayer() const { return m_pPlayer; }
private:
	float m_SceneTime;
	bool m_Initialized;
	bool m_Paused;
	Game* m_pGame;
	Player* m_pPlayer;
	Camera* m_pCamera;
	World* m_pWorld;
	EntityManager* m_pEntityManager;
	TextureManager* m_pTextureManager;
	CollisionHandler* m_pCollisionHandler;
};

