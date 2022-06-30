#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

#pragma once
class ObjectGenerator : public Unigine::ComponentBase
{

public:
	COMPONENT_DEFINE(ObjectGenerator, ComponentBase);
	COMPONENT_INIT(init, 1);

	//========================== NEW - BEGIN ===============================
	PROP_PARAM(Node, levelManager);
	//=========================== NEW - END ================================

protected:
	void init();
};