#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineMathLib.h>
#include <UnigineGame.h>

class ColorChanger : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(ColorChanger, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

protected:
	void init();
	void update();

private:
	
	float changeSpeed = 2.5f;

	Unigine::MaterialPtr color_zone_mat;
};