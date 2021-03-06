#include "Mason/CircleCollider2D.h"

#include "Mason/GameObject.hpp"
#include "Mason/PhysicsBody2D.hpp"
#include "Box2D/Box2D.h"

using namespace Mason;

void CircleCollider2D::setCenter(float x, float y) const
{
	center->x = x / Physics::instance->phScale;
	center->y = y / Physics::instance->phScale;
	circleShape->m_p.Set(center->x, center->y);
	
}
/*void CircleCollider2D::setScale(float scale) {
	Collider2D::setScale(scale);

	setSize(scale);
	auto body = gameObject->getComponent<PhysicsBody2D>();
	if (body != nullptr)
		body->UpdateFixtures();
}

void CircleCollider2D::setDensity(float density)
{
	Collider2D::setDensity(density);
	auto body = gameObject->getComponent<PhysicsBody2D>();
	if (body != nullptr) body->UpdateFixtures();
}

void CircleCollider2D::setFriction(float friction)
{
	Collider2D::setFriction(friction);
	auto body = gameObject->getComponent<PhysicsBody2D>();
	if (body != nullptr) body->UpdateFixtures();
}*/

CircleCollider2D::~CircleCollider2D()
{
	delete shape;
	delete radius;
	delete center;
}

void CircleCollider2D::setSize(float rad) const
{
	circleShape->m_radius = rad / Physics::instance->phScale;
}

CircleCollider2D::CircleCollider2D(std::shared_ptr<GameObject> gameObject) : Collider2D(gameObject)
{
	center = new b2Vec2();
	radius = new float();
	circleShape = new b2CircleShape();
	shape = circleShape; //fixture which uses this shape
	setCenter(0, 0);
	setSize(1);
}
