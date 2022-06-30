#pragma once
#include <UnigineComponentSystem.h>

#include "LevelManager.h"
#include "UiElement.h"
#include <UnigineConsole.h>
#include <UnigineApp.h>

class EndWidget : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(EndWidget, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init);

	// object with the end game message
	PROP_PARAM(Node, endGameWidget);

protected:
	void init();

	void endGameEventHandler();
	void onClickHandler(UiElement::Element uiType);

private:
	LevelManager* levelManager;
};