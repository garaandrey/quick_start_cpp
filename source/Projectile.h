#pragma once
#include <UnigineComponentSystem.h>

#include <UnigineGame.h>

class Projectile : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(Projectile, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	PROP_PARAM(File, bulletHitEffect);
	PROP_PARAM(Float, speed);

protected:
	void init();
	void update();

private:
	// speed of the bullet
	//float speed = 30.0f;

	Unigine::WorldIntersectionNormalPtr intersection;
};