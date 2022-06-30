#include "KillZone.h"

using namespace Unigine;

REGISTER_COMPONENT(KillZone);

void KillZone::init()
{
	trigger = checked_ptr_cast<WorldTrigger>(node);

	// set the callback to be executed when an object enters the area
	if (trigger)
		trigger->addEnterCallback(MakeCallback(this, &KillZone::enterCallback));
}

//========================== NEW - BEGIN ===============================
void KillZone::enterCallback(NodePtr target)
{
	levelManager = getComponentInParent<LevelManager>(target);
	// check if the parent node has a LevelManager component attached
	if (levelManager)
	{
		// delete the entered node and decrease the amount of physical objects
		levelManager->decPhysicalObjectsNum();
		target->deleteLater();
	}
}
//=========================== NEW - END ================================