#include "MusicPlayer.h"

REGISTER_COMPONENT(MusicPlayer);

using namespace Unigine;

void MusicPlayer::init()
{
	music = AmbientSource::create(background_music);
	music->setLoop(1);
	music->setGain(0.5f);
	// start playing the music on initialization
	music->play();
}

void MusicPlayer::shutdown()
{
	if (music)
		music->deleteLater();
}