#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "CollisionBody.h"
#include "CollisionHandler.h"

CollisionBody::CollisionBody(Component* Instance) :
	m_Active{ true },
	m_IsGrounded{false},
	m_IsWallbound{false},
	m_Tag{"Default"},
	m_Instance{ Instance },
	m_pCollisionHandler{nullptr}
{

}

CollisionBody::~CollisionBody()
{
}

void CollisionBody::DrawCollider() const
{
	utils::DrawPolygon(m_Vertices, true, 1.f);
	//std::cout << m_Vertices.size() << std::endl;
}

void CollisionBody::UpdateCollider(float elapsedSec)
{
	// This will calculate a default hitbox based on the transform of the instance !
	const Vector2f position{ m_Instance->GetTransform()->GetPosition() };
	const float width{ m_Instance->GetTransform()->GetWidth() };
	const float height{ m_Instance->GetTransform()->GetHeight() };

	Point2f origin(position.x, position.y);
	std::vector<Point2f> updatedVertices{
		Point2f(origin.x,origin.y),
		Point2f(origin.x + width,origin.y),
		Point2f(origin.x + width,origin.y + height),
		Point2f(origin.x,origin.y + height),
	};
	SetVertices(updatedVertices);
}

void CollisionBody::ApplyDefaultCollisions()
{
	if (IsActive()) {
		Transform* bodyTransform{ m_Instance->GetTransform() };
		const float bodyWidth{ bodyTransform->GetWidth() };
		const float bodyHeight{ bodyTransform->GetHeight() };
		const Vector2f position{ bodyTransform->GetPosition() };
		const Vector2f origin{ position + Vector2f{bodyWidth/2,bodyHeight/2}};
		const Vector2f minimumVelocity( float(0),float(0) );
		const Vector2f currentVelocity{ bodyTransform->GetCurrentVelocity() + minimumVelocity };

		const float lookDirection{ bodyTransform->GetLookDirection() };
		const float upDirection{ abs(currentVelocity.y) / currentVelocity.y };
		const float yRayLength{ (bodyHeight / 2)  };

		const Vector2f upVector{ origin + Vector2f{ 0 , yRayLength * upDirection }}; 

		utils::HitInfo upCollision{ CheckCollision(origin, upVector,{"Collidable"}) };
		Vector2f positionPostCollision{ position };
		Vector2f velocityPostCollision{ bodyTransform->GetVelocity() };

		if (upCollision.lambda != -1) { // if something is hit
			positionPostCollision.y = upCollision.intersectPoint.y;// + (bodyHeight - (bodyHeight * upDirection) ));
			velocityPostCollision.y = 0;
			m_IsGrounded = true;
			//bodyTransform->SetAcceleration(0);
		} else {
			m_IsGrounded = false;
		} 
		 
		bodyTransform->SetVelocity(velocityPostCollision);
		bodyTransform->SetPosition(positionPostCollision);
		//std::cout << "X -> " << currentVelocity.x << " : Y -> " << currentVelocity.y << std::endl;

		//std::cout << " X hit -> " << lookCollision.lambda << " - Y hit -> " << upCollision.lambda << std::endl;
	}
}

bool CollisionBody::FrontCollision(const Vector2f& pos)
{
	Transform* bodyTransform{ m_Instance->GetTransform() };
	const float bodyWidth{ bodyTransform->GetWidth() };
	const float bodyHeight{ bodyTransform->GetHeight() };
	const Vector2f position{ pos };
	const Vector2f origin{ position + Vector2f{bodyWidth / 2,bodyHeight / 2} };
	const Vector2f minimumVelocity(float(0), float(0));
	const Vector2f currentVelocity{ (position - bodyTransform->GetPosition()) + minimumVelocity };

	const float lookDirection{ abs(currentVelocity.x) / currentVelocity.x };
	const float xRayLength{ (bodyWidth / 2)  };

	const Vector2f lookVector{ origin + Vector2f{ (xRayLength * lookDirection) , currentVelocity.y * (xRayLength * 1.25f) } };
	utils::HitInfo lookCollision{ CheckCollision(origin, lookVector,{"Collidable"})};

	bool isColliding{ (IsActive() && (lookCollision.lambda != -1)) };
	if (isColliding) {
		m_IsWallbound = true;
	}
	else {
		m_IsWallbound = false;
	}
	return isColliding;
}

utils::HitInfo CollisionBody::CheckCollision(const Vector2f& from, const Vector2f& target,const std::vector<std::string>& tags)
{
	std::vector<CollisionBody*> m_Bodies{ m_pCollisionHandler->GetBodies() };
	utils::HitInfo hitResult;
	hitResult.lambda = -1;

	for (size_t collisionBodyIndex{}; collisionBodyIndex < m_Bodies.size(); collisionBodyIndex++) {
		const CollisionBody* currentBody{ m_Bodies[collisionBodyIndex] };
		const bool hasTag{ std::find(tags.begin(), tags.end(), currentBody->GetTag() ) != tags.end() };
		utils::HitInfo ray;

		if (currentBody != this && hasTag) {
			bool rayHit{ utils::Raycast(currentBody->GetVertices(), from.ToPoint2f(), target.ToPoint2f(), ray) };
			if (rayHit) {
				hitResult = ray;
				break;
			}
		}
		
	};

	return hitResult;
}

Rectf CollisionBody::GetRect() const
{
	const Vector2f Position{ m_Instance->GetTransform()->GetPosition() };
	return Rectf(
		Position.x,
		Position.y,
		m_Instance->GetTransform()->GetWidth(),
		m_Instance->GetTransform()->GetHeight()
	);
}


void CollisionBody::SetVertices(const std::vector<Point2f>& newVertices)
{
	m_Vertices = newVertices;
}

