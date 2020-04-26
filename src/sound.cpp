#include "sound.h"

#include <SDL_mixer.h>
#include <ostream>

#include "debug.h"

void Sound::load(const std::string& path) {
	if (sound) Mix_FreeChunk(sound);
	sound = Mix_LoadWAV(path.c_str());
	if (!sound) {
		Debug::out << "Unable to load sound '" << path << "': " << Mix_GetError();
	}
}

Sound::~Sound() {
	if (sound) Mix_FreeChunk(sound);
}

void Sound::setVolume(float v) { //from 0 to 100
	Mix_VolumeChunk(sound, v * (128 / 100.f));
}

void Sound::play() {
	Mix_PlayChannel(-1, sound, 0);
}

namespace MusicPlayer
{
	Mix_Music* toPlayAfterIntro;
	void introFinishedHook() { Mix_PlayMusic(toPlayAfterIntro, -1); }

	void Play(Mix_Music* music) {
		Mix_PlayMusic(music, -1);
	}
	
	void PlayWithIntro(Mix_Music* music, Mix_Music* intro) {
		Mix_PlayMusic(intro, 1);
		toPlayAfterIntro = music;
		Mix_HookMusicFinished(introFinishedHook);
	}

	void Pause() {
		Mix_PauseMusic();
	}
	void Resume() {
		Mix_ResumeMusic();
	}

	void Stop() {
		Mix_HaltMusic();
	}

	void SetVolume(float volume) {
		Mix_VolumeMusic(volume * (128 / 100.f));
	}
	
	float GetVolume(float volume) {
		return Mix_VolumeMusic(-1) * (100 / 128.f);
	}
}