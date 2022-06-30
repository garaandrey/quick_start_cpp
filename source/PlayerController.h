#pragma once
#include <UnigineComponentSystem.h>

#include <UnigineGame.h>
#include <UnigineControls.h>
#include <UnigineStreams.h>
#include <UniginePlayers.h>
#include <UnigineWorld.h>
#include <UnigineConsole.h>
#include <UnigineMathLib.h>
#include <UnigineApp.h>
#include <UnigineRender.h>

class PlayerController : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(PlayerController, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init);
	COMPONENT_UPDATE_PHYSICS(updatePhysics);

	COMPONENT_UPDATE(update);

	// asset file that contains the bullet
	PROP_PARAM(File, bullet_path);
	// nodes in the world for bullets' spawn
	PROP_PARAM(Node, leftSpawn);
	PROP_PARAM(Node, rightSpawn);

protected:
	void init();
	void updatePhysics();
	void update();

private:
	void move(const Unigine::Math::vec3& direction);

	Unigine::PlayerPtr player;

	// a WorldIntersection object to store the information about the intersection
	Unigine::WorldIntersectionPtr intersection = Unigine::WorldIntersection::create();

	Unigine::Math::vec3 pos;

	Unigine::BodyRigidPtr rigid;

	bool isNextLeft = false;

	// mouse fire button 
	Unigine::Input::MOUSE_BUTTON mouseFireKey = Unigine::Input::MOUSE_BUTTON::MOUSE_BUTTON_RIGHT;

	Unigine::NodePtr bullet;
};