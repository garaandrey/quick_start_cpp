#pragma once
#include <UnigineComponentSystem.h>

#include <UnigineSounds.h>

class MusicPlayer : public Unigine::ComponentBase
{
public:
	// declare constructor and destructor for our class and define a property name. 
	COMPONENT_DEFINE(MusicPlayer, ComponentBase)
		// declare methods to be called at the corresponding stages of the execution sequence
		COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);
	// background music asset
	PROP_PARAM(File, background_music);

protected:
	void init();
	void shutdown();

private:
	Unigine::AmbientSourcePtr music;
};