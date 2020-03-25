#include "Sounds.h"

ISoundEngine* SoundEngine = createIrrKlangDevice();

void Sounds::playMusic(bool& playing) {
	SoundEngine->stopAllSounds();
	if (playing) SoundEngine->play2D("audio/playing-music.mp3", GL_FALSE);
	else SoundEngine->play2D("audio/menu-music.mp3", GL_TRUE);
}

void Sounds::playSoundEffect(const string& effect){
	if (effect == "MOVE") SoundEngine->play2D("audio/move.mp3", GL_FALSE);
	else if (effect == "ROCK") SoundEngine->play2D("audio/rock.mp3", GL_FALSE);
	else if (effect == "DIE") SoundEngine->play2D("audio/die.mp3", GL_FALSE);
	else if (effect == "WIN") SoundEngine->play2D("audio/win.mp3", GL_FALSE);
	else if (effect == "MENU") SoundEngine->play2D("audio/menu-selector.wav", GL_FALSE);
}