#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

class Destroy : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(Destroy, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// object's lifetime
	PROP_PARAM(Float, lifeTime);

protected:
	void init();
	void update();

private:
	float startTime;
};