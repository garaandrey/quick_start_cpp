#include "Destroy.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(Destroy);

void Destroy::init()
{
	// remember initialization time of an object
	startTime = Game::getTime();
}

void Destroy::update()
{
	// wait until the life time ends and delete the object
	if (Game::getTime() - startTime > lifeTime)
		node->deleteLater();
}