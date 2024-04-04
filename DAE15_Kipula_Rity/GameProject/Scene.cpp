
#include <chrono>
#include <ctime>
#include "pch.h"
#include "Scene.h"
#include "Camera.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "Game.h"
#include "Transform.h"

Scene::Scene(Game* game) :
	m_pGame{ game },
	m_SceneTime{ 0 },
	m_Initialized{ false },
	m_Paused{ false },
	m_pWorld{nullptr},
	m_pPlayer{nullptr}
{
	m_pCamera = new Camera(game->GetViewPort());
	m_pTextureManager = new TextureManager();
	m_pCollisionHandler = new CollisionHandler();
	m_pEntityManager = new EntityManager(m_pTextureManager);
}

Scene::~Scene()
{
	delete m_pCamera;
	delete m_pEntityManager;
	delete m_pTextureManager;
	delete m_pCollisionHandler;
	delete m_pWorld;
}

void Scene::Initialize(const std::string& worldName)
{
	if (!m_Initialized) {
		const WorldData worldData{ m_pGame->GetScenes()[worldName] };

		m_pWorld = new World(worldData, m_pTextureManager);
		m_pWorld->SetWorldScale(3);
		m_pCollisionHandler->AddBody(new CollisionBody(m_pWorld));

		m_pPlayer = new Player(m_pEntityManager, Vector2f{ 0,500.f }, "Kirby");
		// Change spawn point dependant on world data later??? Maybe throw in an extra parameter so I can choose where you land!!
		m_pCollisionHandler->AddBody(new CollisionBody(m_pPlayer));

		m_Initialized = true;
		m_SceneTime = 0;
	}
}

void Scene::Update(float elapsedSec)
{   
	if (m_Initialized&&!m_Paused) {
		m_SceneTime += elapsedSec;
		m_pEntityManager->UpdateEntities(elapsedSec);
		m_pWorld->Update(elapsedSec);
	}
}

void Scene::Draw() const
{
	if (m_Initialized) {
		m_pCamera->DrawCamera(m_pWorld, m_pPlayer->GetTransform()->GetPosition());
		m_pWorld->Draw();
		m_pEntityManager->DrawEntities();
		m_pCamera->Reset(); // reset camera matrix! 
	}
}

