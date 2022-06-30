#include "EndWidget.h"

using namespace Unigine;

REGISTER_COMPONENT(EndWidget);

void EndWidget::init()
{
	levelManager = ComponentSystem::get()->getComponent<LevelManager>(World::getNodeByName("level_manager"));

	if (levelManager)
		levelManager->setEndGameCallback(MakeCallback(this, &EndWidget::endGameEventHandler));

	// set the mouse click handler for UI elements (Restart/Exit)
	UiElement::setOnClickCallback(MakeCallback(this, &EndWidget::onClickHandler));

	if (endGameWidget)
	{
		// hide the end UI
		endGameWidget->setEnabled(false);
	}
}

void EndWidget::endGameEventHandler()
{
	// set gui and input
	Input::setMouseHandle(Input::MOUSE_HANDLE::MOUSE_HANDLE_USER);

	// show the end UI
	endGameWidget->setEnabled(true);
}

void EndWidget::onClickHandler(UiElement::Element uiType)
{
	// restart the level by reloading the world
	if (uiType == UiElement::Element::Restart)
	{
		Unigine::Console::run("world_reload");
	}

	// exit the game
	if (uiType == UiElement::Element::Exit)
		App::exit();
}