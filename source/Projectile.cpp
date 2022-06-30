#include "Projectile.h"
#include "Destroy.h"

REGISTER_COMPONENT(Projectile);

using namespace Unigine;
using namespace Math;

void Projectile::init()
{
	if (intersection == nullptr)
		intersection = WorldIntersectionNormal::create();
}

void Projectile::update()
{
	vec3 oldPos = node->getWorldPosition();
	vec3 dir = node->getWorldDirection(MathLib::AXIS::AXIS_Y);

	// calculate the next position of the bullet
	vec3 newPos = oldPos + dir * speed * Game::getIFps();

	// check the intersection with wall objects
	Unigine::ObjectPtr obj = World::getIntersection(oldPos, newPos, 0x00000080, intersection); // 7th BulletIntersection bit is set
	if (obj)
	{
		// spawn the hit effect at the hit point
		NodePtr hitEffect = World::loadNode(bulletHitEffect);
		if (hitEffect)
		{
			hitEffect->setPosition(intersection->getPoint());
			// orient the effect towards the hit direction 
			hitEffect->setWorldDirection(intersection->getNormal(), vec3_up, AXIS::AXIS_Y);
		}

		// add impulse to an object if it is a body rigid 
		BodyRigidPtr rb = obj->getBodyRigid();
		if (rb)
		{
			rb->setFrozen(false);
			rb->addWorldImpulse(obj->getWorldPosition(), node->getWorldDirection(MathLib::AXIS::AXIS_Y) * speed);
		}

		// remove the bullet
		node->deleteLater();
	}
	else
	{
		// move the bullet to a new position
		node->setWorldPosition(newPos);
	}
}