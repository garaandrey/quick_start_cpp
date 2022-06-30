#include "LevelManager.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(LevelManager);

void LevelManager::init()
{
	LevelManager::initGUI();

	// find the object text node of the widget
	endText = checked_ptr_cast<ObjectText>(Game::getPlayer()->findNode("header_text", 1));

	// count dynamic objects in the level
	physicalObjectsNum = node->getNumChildren();

	//========================== NEW - BEGIN ===============================
		// set up the restart button as a UI element
	if (restartButton)
	{
		UiElement* restart_component = ComponentSystem::get()->addComponent<UiElement>(restartButton);
		restart_component->uiType = UiElement::Element::Restart;
		restart_component->uiMask = 0x00000040; // 6th bit is set
		restart_component->selectScale = 1.05f;
	}

	// set up the exit button as a UI element
	if (exitButton)
	{
		UiElement* exit_component = ComponentSystem::get()->addComponent<UiElement>(exitButton);
		exit_component->uiType = UiElement::Element::Exit;
		exit_component->uiMask = 0x00000040; // 6th bit is set
	}
	//=========================== NEW - END ================================
}

void LevelManager::initGUI()
{
	// get a GUI pointer
	GuiPtr gui = Gui::get();

	// create a label widget and set up its parameters
	widget_timer = WidgetLabel::create(gui, "Time Left:");
	widget_timer->setPosition(10, 10);
	widget_timer->setFontColor(vec4_red);

	widget_goal = WidgetLabel::create(gui, "Objects Left: ");
	widget_goal->setPosition(10, 30);
	widget_goal->setFontColor(vec4_blue);

	// add widgets to the GUI
	gui->addChild(widget_timer, Gui::ALIGN_OVERLAP);
	gui->addChild(widget_goal, Gui::ALIGN_OVERLAP);
}

void LevelManager::update()
{
	// decrease the timer
	if (isCounting)
	{
		timer = timer - Game::getIFps();
		if (timer <= 0)
		{
			//set end game text
			endText->setText("Game Over");
			if (endGameEvent) endGameEvent->run();
			isCounting = false;
		}
	}

	// show the current time and objects left to clear
	if (isCounting)
	{
		widget_timer->setText(String::format("Time Left: %.2f s", timer.get()));
		widget_goal->setText(String::format("Objects Left: %d", physicalObjectsNum));
	}
	//hide the widgets on endgame
	else
	{
		widget_timer->setEnabled(false);
		widget_goal->setEnabled(false);
	}

	//win
	if (physicalObjectsNum <= 0)
	{
		endText->setText("Success!");
		if (endGameEvent) endGameEvent->run();
		isCounting = false;
	}
}

void LevelManager::shutdown()
{
	widget_timer->deleteLater();
	widget_goal->deleteLater();
}

void LevelManager::decPhysicalObjectsNum()
{
	physicalObjectsNum--;
}