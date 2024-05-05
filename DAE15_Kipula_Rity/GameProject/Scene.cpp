
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
#include "GUI.h"	


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
	m_pGUI = new GUI(this);
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
	delete m_pGUI;
}

void Scene::Initialize(const std::string& worldName)
{
	if (!m_Initialized) {
		const WorldData worldData{ m_pGame->GetScenes()[worldName] };

		m_pWorld = new World(worldData, m_pTextureManager);
		m_pWorld->SetWorldScale(worldData.scale);
		m_pWorld->CreateCollisions(m_pCollisionHandler);
		 
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
		// Platform update 
		if (this->GetPlayer() != nullptr) {
			const Transform* playerTransform{ this->GetPlayer()->GetTransform() };
			const Vector2f playerPosition{ playerTransform->GetPosition() };
			const std::vector<CollisionBody*> platforms{ m_pWorld->GetPlatforms() };
			//std::cout << playerPosition.y << std::endl;

			for (size_t platformIndex{}; platformIndex < platforms.size(); platformIndex++) {
				CollisionBody* platform{ platforms[platformIndex] };
				const Rectf platformRect{ platform->GetRect() };
				const float platformY{ platform->GetVerticesPosition().y };
				 
				platform->SetActive(playerPosition.y > platformY);
			}
		} 

		m_pSpawnerManager->Update(elapsedSec);
		m_pEntityManager->UpdateEntities(elapsedSec);
		m_pCamera->UpdateCamera(elapsedSec, m_pWorld, m_pPlayer->GetTransform()->GetPosition() );
		m_pWorld->Update(elapsedSec);
		m_pGUI->Update(elapsedSec);
	}

	if (m_Destroying) {
		m_SceneInactiveTime += elapsedSec;
	}
	m_SceneTime += elapsedSec;
}

void Scene::Draw() const
{
	if (m_Initialized) {
		glPushMatrix();
		glTranslatef(0, GUI_HEIGHT, 0);
		m_pCamera->DrawCamera();
		m_pWorld->Draw();
		m_pEntityManager->DrawEntities();

		// Show collisions
		/*for (size_t collisionIndex{}; collisionIndex < m_pCollisionHandler->GetBodies().size(); collisionIndex++) {
			if (m_pCollisionHandler->GetBodies()[collisionIndex]->IsActive()) {
				utils::SetColor(Color4f(0, 1, 0, 1));
			}
			else {
				utils::SetColor(Color4f(1, 0, 0, 1));
			}
			utils::DrawPolygon(m_pCollisionHandler->GetBodies()[collisionIndex]->GetVertices(),5);
		}*/

		//

		m_pCamera->Reset(); // reset camera matrix! 
		glPopMatrix();

		m_pGUI->Draw();
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

