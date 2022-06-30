#pragma once
#include <UnigineComponentSystem.h>

#include <UnigineWidgets.h>
#include <UnigineGame.h>
#include <UnigineString.h>
//========================== NEW - BEGIN ===============================
#include "UiElement.h"
//=========================== NEW - END ================================

class LevelManager : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(LevelManager, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init, 2);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);
	// level timer
	PROP_PARAM(Float, timer, 100.0f);

	//========================== NEW - BEGIN ===============================
	PROP_PARAM(Node, restartButton);
	PROP_PARAM(Node, exitButton);
	//=========================== NEW - END ================================

	void decPhysicalObjectsNum();
	void setEndGameCallback(Unigine::CallbackBase* callback) { endGameEvent = callback; }

protected:
	void init();
	void update();
	void shutdown();

	void initGUI();

private:
	Unigine::CallbackBase* endGameEvent = nullptr;

	bool isCounting = true;

	int physicalObjectsNum;

	Unigine::WidgetLabelPtr widget_timer, widget_goal;

	Unigine::ObjectTextPtr endText;
};