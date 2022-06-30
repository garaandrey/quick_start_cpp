#include "UiElement.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(UiElement);

CallbackBase* UiElement::onClickCallback = nullptr;

int UiElement::idCount = 0;

void UiElement::init()
{
	// set ID
	Id = idCount;
	++idCount;

	selectedObjects = 0;

	// get the UI element
	uiObject = checked_ptr_cast<Object>(node);

	// remember the source scale and emission color
	sourceScale = node->getScale();
	if (uiObject)
		sourceEmission = uiObject->getMaterialParameterFloat4("emission_color", 0);

	intersection = WorldIntersection::create();
}

void UiElement::update()
{
	// get points for intersection
	vec3 dir = Game::getPlayer()->getDirectionFromScreen();
	vec3 p0 = Game::getPlayer()->getWorldPosition();
	vec3 p1 = p0 + dir * 25.0f;

	// find the intersection
	ObjectPtr obj = World::getIntersection(p1, p0, uiMask, intersection);
	if (obj)
	{
		// try to get the UI element component and select/deselect it
		UiElement* uiElement = ComponentSystem::get()->getComponent<UiElement>(obj);
		if (uiElement && uiElement->Id == Id)
		{
			if (!isSelect)
			{
				UiElement::onEnter();
				isSelect = true;
				++selectedObjects;
			}
		}
		else if (isSelect)
		{
			UiElement::onLeave();
			isSelect = false;
			--selectedObjects;
		}
	}
	else
	{
		if (isSelect)
		{
			UiElement::onLeave();
			isSelect = false;
			--selectedObjects;
		}
	}

	// run the mouse click callback
	if (isSelect && Input::isMouseButtonDown(Input::MOUSE_BUTTON::MOUSE_BUTTON_LEFT) && onClickCallback)
		onClickCallback->run(uiType);
}

void UiElement::onDisable()
{
	// deselect an object
	if (isSelect)
	{
		--selectedObjects;
		if (selectedObjects < 0)
			selectedObjects = 0;

		isSelect = false;
		UiElement::onLeave();
	}
}

void UiElement::onEnter()
{
	// set the visual effect on selection
	node->setScale(sourceScale * selectScale);
	uiObject->setMaterialParameterFloat4("emission_color", selectEmission, 0);
}

void UiElement::onLeave()
{
	// remove the visual effect when the UI element is not selected anymore
	node->setScale(sourceScale);
	uiObject->setMaterialParameterFloat4("emission_color", sourceEmission, 0);
}