#include "pch.h"
#include "iostream"
#include "Game.h"
#include "Player.h"
#include "Transform.h"
#include "AnimationController.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pCamera = new Camera(GetViewPort());
	m_pEntityManager = new EntityManager();
	m_pTextureManager = new TextureManager();
	m_pCollisionHandler = new CollisionHandler();

	m_pWorld = new World(WorldData{"VegetableValley",3.f,1}, m_pTextureManager);
	m_pWorld->SetWorldScale(3);
	m_pCollisionHandler->AddBody( new CollisionBody(m_pWorld) );

	m_Player = new Player(m_pEntityManager, Vector2f{0,250.f}, "Kirby");
	m_Player->GetAnimator()->SetTextureManager(m_pTextureManager);
	m_pCollisionHandler->AddBody( new CollisionBody(m_Player) );
} 

void Game::Cleanup( )
{
	delete m_pEntityManager; 
	delete m_pTextureManager;
	delete m_pCollisionHandler;
	delete m_pWorld;
	delete m_pCamera;
}

void Game::Update( float elapsedSec )
{
	m_pEntityManager->UpdateEntities(elapsedSec);
	m_pWorld->Update(elapsedSec);
	//std::cout << m_EntityManager->GetEntities().size() << std::endl;
}

void Game::Draw( ) const
{
	ClearBackground( );
	//m_pWorld->Draw();

	m_pCamera->DrawCamera(m_pWorld, m_Player->GetTransform()->GetPosition());
	m_pWorld->Draw();
	m_pEntityManager->DrawEntities();
	m_pCamera->Reset(); // reset camera matrix! 
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
