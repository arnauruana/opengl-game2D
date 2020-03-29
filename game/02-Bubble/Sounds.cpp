#include "Sounds.h"

ISoundEngine* SoundEngine = createIrrKlangDevice();

void Sounds::playMusic(bool playing) {
	stop();
	if (!muted) {
		//if (playing) SoundEngine->play2D("audio/play-music.wav", GL_FALSE); //Music by Michorvath
		//else SoundEngine->play2D("audio/menu-music.wav", GL_TRUE);   //Music by Chizmaster
	}

}

void Sounds::playSoundEffect(const string& effect) {
	if (!muted) {
		if (effect == "MOVE") SoundEngine->play2D("audio/move.wav", GL_FALSE);
		else if (effect == "PUSH") SoundEngine->play2D("audio/push.wav", GL_FALSE);
		else if (effect == "DIE") SoundEngine->play2D("audio/die.wav", GL_FALSE);
		else if (effect == "WIN") SoundEngine->play2D("audio/win.wav", GL_FALSE);
		else if (effect == "MENU") SoundEngine->play2D("audio/menu-selector.wav", GL_FALSE);
	}



}

void Sounds::stop() {
	SoundEngine->stopAllSounds();
}