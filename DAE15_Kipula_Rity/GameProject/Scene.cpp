
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
#include "Enemy.h"
#include "EnemySpawner.h"
#include "EnemySpawnerHandler.h"
#include "Transform.h"


Scene::Scene(Game* game, SceneManager* manager) :
	m_pGame{ game },
	m_pSceneManager{ manager },
	m_SceneTime{ 0 },
	m_SceneInactiveTime{ 0 },
	m_SceneTransitionTime{ SCENE_TRANSITION_TIME },
	m_Initialized{ false },
	m_Paused{ false },
	m_Destroying{ false },
	m_pWorld{nullptr},
	m_pPlayer{nullptr}
{
	m_pCamera = new Camera(game->GetViewPort());
	m_pSpawnerManager = new EnemySpawnerHandler(this);
	m_pTextureManager = new TextureManager();
	m_pCollisionHandler = new CollisionHandler();
	m_pEntityManager = new EntityManager(this);
}

Scene::Scene(Game* game, SceneManager* manager, float transitionTime): 
	Scene(game,manager)
{ 
	m_SceneTransitionTime = transitionTime;
}

Scene::~Scene()
{
	delete m_pCamera;
	delete m_pSpawnerManager;
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
		m_pWorld->SetWorldScale(worldData.scale);
		m_pWorld->CreateCollisions(m_pCollisionHandler);
		/*m_pCollisionHandler->AddBody(new CollisionBody(m_pWorld));
		m_pWorld->GetCollisionBody()->SetTag("Collidable");*/
		 
		m_pPlayer = new Player(m_pEntityManager, Vector2f{ 200.f,200.f }, "Kirby");
		// Change spawn point dependant on world data later??? Maybe throw in an extra parameter so I can choose where you land!!

		for (size_t spawnerIndex{}; spawnerIndex < worldData.spawners.size(); spawnerIndex++) {
			SpawnerData spawnerData{ worldData.spawners[spawnerIndex] };
			m_pSpawnerManager->CreateSpawner(new EnemySpawner(spawnerData.typeSpawner, spawnerData.position, spawnerData.amountEnemies));
		}

		m_Initialized = true;
		m_SceneTime = 0;
	}
}

void Scene::Update(float elapsedSec)
{   
	if (m_Initialized and not m_Paused and not m_Destroying) {
		m_pSpawnerManager->Update(elapsedSec);
		m_pEntityManager->UpdateEntities(elapsedSec);
		m_pCamera->UpdateCamera(elapsedSec, m_pWorld, m_pPlayer->GetTransform()->GetPosition() );
		m_pWorld->Update(elapsedSec);
		//std::cout << m_pPlayer->GetTransform()->GetPosition().x << std::endl;
	}

	if (m_Destroying) {
		m_SceneInactiveTime += elapsedSec;
	}
	m_SceneTime += elapsedSec;
}

void Scene::Draw() const
{
	if (m_Initialized) {
		m_pCamera->DrawCamera();
		m_pWorld->Draw();
		m_pEntityManager->DrawEntities();
		m_pCamera->Reset(); // reset camera matrix! 
	}
}

void Scene::Destroy()
{
	if (not m_Destroying) {
		m_Destroying = true;
		SetPause(true);
	}
}

bool Scene::IsReady() const
{
	return 
		(m_Initialized)
		and (m_SceneTime > m_SceneTransitionTime);
}

