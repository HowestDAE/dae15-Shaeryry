#include "pch.h"
#include "Player.h" 
#include "Entity.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Transform.h"
#include <map>

Player::Player(EntityManager* manager, const Vector2f& origin, const std::string& entityName)
	: Entity(manager,origin,entityName)
{ 
	//this->GetTransform()->SetPosition(Vector2f{ 125.f,250.f });

	std::map<int, AnimationData> playerTracks{};
	playerTracks[1] = AnimationData{"Idle",2,2,true};
	playerTracks[2] = AnimationData{ "Run",4,Animation::DEFAULT_ANIMATION_UPDATE,true };

	this->SetAnimationData(playerTracks);

	/*Animation* IdleAnimation{m_pAnimator->PlayAnimation("Idle",2,0)};
	IdleAnimation->Loop(true); 
	IdleAnimation->SetUpdateTime(2);*/

	/*Animation* RunAnimation{m_pAnimator->PlayAnimation("Run",4,1)};
	RunAnimation->SetUpdateTime(1);*/
}

void Player::Update(float elapsedSec) 
{ 
	Entity::Update(elapsedSec);
	//this->GetTransform()->Update(elapsedSec);
	this->UpdateKeyboard(elapsedSec);
}

void Player::UpdateKeyboard(float elapsedSec)
{
	Vector2f currentPosition{ this->GetTransform()->GetPosition() };
	Vector2f direction(0, 0);

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT]) {
		direction.x = 1;
	}
	else if (pStates[SDL_SCANCODE_LEFT]) {
		direction.x = -1;
	};

	if (pStates[SDL_SCANCODE_SPACE]) {
		//direction.y = 1;
		//Jump Logic
	}

	Vector2f movement{
		((direction.Normalized().x * m_MovementSpeed) * elapsedSec),
		0
	};
	Vector2f newPosition{ currentPosition + movement };
	Vector2f velocity{ (newPosition - currentPosition) };

	// STATE UPDATE
	if (abs(velocity.x) > 0) {
		//m_State = EntityState::Run;
		SetState(EntityState::Run);
	}
	else {
		//m_State = EntityState::Idle;
		SetState(EntityState::Idle);
	};

	//std::cout << "Flip = " << velocity.x << std::endl;
	this->GetTransform()->SetPosition(newPosition);
}

