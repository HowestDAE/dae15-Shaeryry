#pragma once
#include "BaseGame.h"
#include "SceneManager.h"
#include "Scene.h"
#include "World.h"

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();
	
	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

	// Custom Methods
	std::map<std::string, WorldData> GetScenes() const { return m_Scenes; };
	PlayerData& GetPlayerData() { return m_SavedPlayerData; };
	void ResetPlayerData();
private:
	SceneManager* m_SceneManager;
	std::map<std::string, WorldData> m_Scenes;
	PlayerData m_SavedPlayerData;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};