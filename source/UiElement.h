#pragma once
#include <UnigineComponentSystem.h>

#include <UnigineApp.h>
#include <UnigineGame.h>


class UiElement : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(UiElement, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	enum Element { Restart, Exit, None };

	// default type of a UI element
	Element uiType = Element::None;

	// scale on cursor hover
	float selectScale = 1;

	// emission color on cursor hover
	Unigine::Math::vec4 selectEmission = Unigine::Math::vec4_black;

	// default mask for the mouse intersection detection
	int uiMask = 1;

	static void setOnClickCallback(Unigine::CallbackBase* callback) { onClickCallback = callback; }

protected:
	void init();
	void update();

	void onWindowResize();
	void onDisable();
	void onLeave();
	void onEnter();

private:
	static Unigine::CallbackBase* onClickCallback;

	// ID of the UI element
	int Id;

	// ID counter for initialization  
	static int idCount;

	// counter of selected objects
	int selectedObjects = 0;

	Unigine::WorldIntersectionPtr intersection;

	bool isSelect = false;

	Unigine::ObjectPtr uiObject = nullptr;

	Unigine::Math::vec3 sourceScale = Unigine::Math::vec3_one;
	Unigine::Math::vec4 sourceEmission = Unigine::Math::vec4_one;
};