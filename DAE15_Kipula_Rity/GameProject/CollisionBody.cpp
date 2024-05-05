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
		const Vector2f origin{ position + Vector2f((bodyWidth / 2),(bodyHeight / 2)) };
		const Vector2f minimumVelocity( float(0),float(0) );
		const Vector2f currentVelocity{ bodyTransform->GetCurrentVelocity() + minimumVelocity };

		const float lookDirection{ abs(currentVelocity.x) / currentVelocity.x };
		const float upDirection{abs(currentVelocity.y) / currentVelocity.y };
		const float xRayLength{ (bodyWidth / 2) };
		const float yRayLength{ (bodyHeight / 2) };

		const Vector2f upVector{ origin + Vector2f(0 , (yRayLength * upDirection)) };
		const Vector2f lookVector{ origin + Vector2f( (xRayLength * lookDirection) , 0 ) };

		utils::HitInfo upCollision{ CheckCollision(origin, upVector + currentVelocity,{"Collidable"})};
		utils::HitInfo lookCollision{ CheckCollision(origin, lookVector + currentVelocity,{"Collidable"}) };

		Vector2f positionPostCollision{ position };
		Vector2f velocityPostCollision{ bodyTransform->GetVelocity() };


		if (upCollision.lambda != -1) {
			positionPostCollision.y = (upCollision.intersectPoint.y-1); 
			velocityPostCollision.y = 0; 
			m_IsGrounded = true;
		}
		else {
			m_IsGrounded = false;
		}

		if (lookCollision.lambda != -1) {
			const float DOT_PRODUCT_WALL{ lookVector.Normalized().DotProduct(lookCollision.normal) };
			if (abs(DOT_PRODUCT_WALL) > .95f) {
				float xPos{ lookCollision.intersectPoint.x };
				if (lookDirection > 0) {
					xPos -= (bodyWidth);
				}
				positionPostCollision.x = xPos;
				velocityPostCollision.x = 0;
				m_IsWallbound = true;
			}
			else {
				m_IsWallbound = false;
			}
		}
		else {
			m_IsWallbound = false;
		}
		
		bodyTransform->SetVelocity(velocityPostCollision);
		bodyTransform->SetPosition(positionPostCollision);

		m_FrontCollision = lookCollision;
		m_FloorCollision = upCollision;
	}
}

utils::HitInfo CollisionBody::CheckCollision(const Vector2f& from, const Vector2f& target,const std::vector<std::string>& tags)
{
	const std::vector<CollisionBody*> bodies{ m_pCollisionHandler->GetBodies() };
	utils::HitInfo hitResult;
	hitResult.lambda = -1;


	for (size_t collisionBodyIndex{}; collisionBodyIndex < bodies.size(); collisionBodyIndex++) {
		const CollisionBody* currentBody{ bodies[collisionBodyIndex] };
		const bool hasTag{ std::find(tags.begin(), tags.end(), currentBody->GetTag() ) != tags.end() };
		const bool IsActive{ currentBody->IsActive() };
		//std::cout << "#" << collisionBodyIndex << " is active > " << IsActive << std::endl;


		if (currentBody != this && hasTag) {
			if (IsActive) { 
				utils::HitInfo ray;
				bool rayHit{ utils::Raycast(currentBody->GetVertices(), from.ToPoint2f(), target.ToPoint2f(), ray) };
				if (rayHit) {
					//std::cout << "standing on #" << collisionBodyIndex << std::endl;

					hitResult = ray;
					//break;
				}
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

Vector2f CollisionBody::GetVerticesPosition() const
{
	float xPosition{ 0 };
	float yPosition{ 0 };

	for (size_t verticesIndex{ 0 }; verticesIndex < m_Vertices.size(); verticesIndex++) {
		xPosition += m_Vertices[verticesIndex].x;
		yPosition += m_Vertices[verticesIndex].y;
	}

	xPosition = xPosition / float(m_Vertices.size());
	yPosition = yPosition / float(m_Vertices.size());


	return Vector2f(xPosition,yPosition);
}


void CollisionBody::SetVertices(const std::vector<Point2f>& newVertices)
{
	m_Vertices = newVertices;
}

