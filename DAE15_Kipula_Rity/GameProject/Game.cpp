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
	// Load scenes hashmap so it's easy to load between the "worlds" !
	m_Scenes["Vegetable Valley 1"] = WorldData{ "VegetableValley",3.f,1 };
	m_SceneManager = new SceneManager();

	Scene* newScene{ new Scene(this) };
	newScene->Initialize("Vegetable Valley 1");
	m_SceneManager->AddScene(newScene);

}

void Game::Cleanup( )
{
	delete m_SceneManager;
}

void Game::Update( float elapsedSec )
{
	m_SceneManager->Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground();
	m_SceneManager->DrawScenes(GetViewPort());
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (m_SceneManager->GetCurrentScene()->GetPlayer() != nullptr) {
		m_SceneManager->GetCurrentScene()->GetPlayer()->OnKeyDownEvent(e);
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	if (m_SceneManager->GetCurrentScene()->GetPlayer() != nullptr) {
		m_SceneManager->GetCurrentScene()->GetPlayer()->OnKeyUpEvent(e);
	}
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
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
