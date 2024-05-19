#pragma once
#include "pch.h"
#include <iostream>
#include "Component.h"

class GUI;
class Camera;
class World;
class EntityManager;
class TextureManager;
class EnemySpawnerHandler;
class CollisionHandler;
class SceneManager;
class Game;
class Player;
class Scene final {
public:
	explicit Scene(Game* game,SceneManager* manager);
	explicit Scene(Game* game, SceneManager* manager,float transitionTime);

	Scene& operator=(const Scene& rhs) = delete;
	Scene(const Scene& other) = delete;
	~Scene();

	void Initialize(const std::string& worldName);
	void Update(float elapsedSec);
	void Draw() const;
	void SetPause(bool paused) { m_Paused = paused; };
	void Destroy();
		
	void SetSceneManager(SceneManager* sceneManager) { m_pSceneManager = sceneManager; };

	bool IsReady() const;
	float GetTransitionTime() const { return m_SceneTransitionTime; };
	float GetSceneTimer() const { return m_SceneTime; };
	float GetSceneInactiveTimer() const { return m_SceneInactiveTime; }; 
	Game* GetGame() const { return m_pGame; };
	Player* GetPlayer() const { return m_pPlayer; };
	Camera* GetCamera() const { return m_pCamera; };
	EntityManager* GetEntityManager() const { return m_pEntityManager; };
	CollisionHandler* GetCollisionHandler() const { return m_pCollisionHandler; };
	SceneManager* GetSceneManager() const { return m_pSceneManager; };
	World* GetWorld() const { return m_pWorld; };
	std::string GetWorldKey() const { return m_WorldKey; };
private:
	std::string m_WorldKey;
	float m_SceneTransitionTime;
	float m_SceneTime;
	float m_SceneInactiveTime;
	float m_ReadyTime;
	bool m_Initialized;
	bool m_Destroying;
	bool m_Paused;

	GUI* m_pGUI;
	Game* m_pGame;
	Player* m_pPlayer;
	Camera* m_pCamera;
	World* m_pWorld;
	EntityManager* m_pEntityManager;
	TextureManager* m_pTextureManager;
	CollisionHandler* m_pCollisionHandler;
	EnemySpawnerHandler* m_pSpawnerManager;
	SceneManager* m_pSceneManager;
};

