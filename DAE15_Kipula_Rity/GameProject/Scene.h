#pragma once
#include "pch.h"
#include <iostream>
#include "Component.h"

class Camera;
class World;
class EntityManager;
class TextureManager;
class EnemySpawnerHandler;
class CollisionHandler;
class Game;
class Player;
class Scene final {
public:
	explicit Scene(Game* game);
	Scene& operator=(const Scene& rhs) = delete;
	Scene(const Scene& other) = delete;
	~Scene();
	void Initialize(const std::string& worldName);
	void Update(float elapsedSec);
	void Draw() const;
	void SetPause(bool paused) { m_Paused = paused; };

	float GetSceneTimer() const { return m_SceneTime; };
	Player* GetPlayer() const { return m_pPlayer; };
	Camera* GetCamera() const { return m_pCamera; };
	EntityManager* GetEntityManager() const { return m_pEntityManager; };
	CollisionHandler* GetCollisionHandler() const { return m_pCollisionHandler; };
	World* GetWorld() const { return m_pWorld; };
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
	EnemySpawnerHandler* m_pSpawnerManager;
};

