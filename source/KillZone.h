#pragma once
#include <UnigineComponentSystem.h>

#include <UnigineWorlds.h>
//========================== NEW - BEGIN ===============================
#include "LevelManager.h"
//=========================== NEW - END ================================

class KillZone : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(KillZone, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init);

protected:
	void init();

	void enterCallback(Unigine::NodePtr target);

private:
	// the area into which an object should fall
	Unigine::WorldTriggerPtr trigger;

	//========================== NEW - BEGIN ===============================
	LevelManager* levelManager;
	//=========================== NEW - END ================================
};