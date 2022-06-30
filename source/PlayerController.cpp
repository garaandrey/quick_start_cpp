#include "PlayerController.h"
#include "Projectile.h"
#include "Destroy.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(PlayerController);

void PlayerController::init()
{
	player = Game::getPlayer();

	if (node)
	{
		rigid = node->getObjectBodyRigid();
		if (rigid)
		{
			rigid->setAngularScale(vec3(0.0f, 0.0f, 0.0f)); // restricting the rotation
			rigid->setLinearScale(vec3(1.0f, 1.0f, 0.0f)); // restricting Z movement
			rigid->setMaxLinearVelocity(8.0f); // clamping the max linear velocity
		}
	}
}

void PlayerController::update()
{
	if (Input::isMouseButtonDown(mouseFireKey) && !Console::isActive())
	{
		// load the bullet and set its position 
		bullet = World::loadNode(bullet_path);

		if (isNextLeft && bullet)
		{
			if (rightSpawn)
			{
				bullet->setPosition(rightSpawn->getWorldPosition());
				bullet->setRotation(rightSpawn->getWorldRotation());
			}
		}
		else
		{
			if (leftSpawn)
			{
				bullet->setPosition(leftSpawn->getWorldPosition());
				bullet->setRotation(leftSpawn->getWorldRotation());
			}
		}
		// alternate between the left and the right gun
		isNextLeft = !isNextLeft;
	}

	// press ESC button to close the game
	if (Input::isKeyDown(Input::KEY::KEY_ESC))
	{
		App::exit();
	}
}

void PlayerController::updatePhysics()
{
	// Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
	// The engine calls updatePhysics() with the fixed rate (60 times per second by default) regardless of the FPS value.
	// WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.

	if (!Console::isActive())  // do not process input if the console is shown
	{
		// check if W key is pressed
		if (Input::isKeyPressed(Input::KEY::KEY_W))
			move(player->getWorldDirection(MathLib::AXIS::AXIS_Y)); // move forward

		// check if S key is pressed
		if (Input::isKeyPressed(Input::KEY::KEY_S))
			move(player->getWorldDirection(MathLib::AXIS::AXIS_NY)); // move backward

		// check if A key is pressed
		if (Input::isKeyPressed(Input::KEY::KEY_A))
			move(player->getWorldDirection(MathLib::AXIS::AXIS_NX)); // move left

		// check if D key is pressed
		if (Input::isKeyPressed(Input::KEY::KEY_D))
			move(player->getWorldDirection(MathLib::AXIS::AXIS_X)); // move right

		// finding the positions of the cursor and the point moved 100 units away in the camera forward direction 
		ivec2 mouse = Input::getMouseCoord();
		vec3 p0 = player->getWorldPosition();
		vec3 p1 = p0 + vec3(player->getDirectionFromScreen(mouse.x, mouse.y)) * 100;

		// casting a ray from p0 to p1 to find the first intersected object
		ObjectPtr obj = World::getIntersection(p0, p1, 1, intersection); // the first bit of the intersection mask is set to 1, the rest are 0s

		// finding the intersection position, creating a transformation matrix to face this position and setting the transform matrix for the body preserving current angular and linear velocities
		if (obj && rigid)
		{
			pos = intersection->getPoint();
			pos.z = rigid->getTransform().getTranslate().z; // project the position vector to the Body Rigid pivot plane
			mat4 transform = Math::setTo(rigid->getTransform().getTranslate(), pos, vec3_up, AXIS::AXIS_Y);
			rigid->setPreserveTransform(transform); // turn the character's body
		}
	}
}

// moving the rigid body with linear impulse in the specified direction
void PlayerController::move(const Unigine::Math::vec3& direction)
{
	if (rigid)
		// direction is a normalized camera axis vector 
		rigid->addLinearImpulse(direction);
}