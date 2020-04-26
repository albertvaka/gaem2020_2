﻿#pragma once

#include <string>

struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

struct Sound
{
	void load(const std::string& file);
	~Sound();

	void setVolume(float v); //from 0 to 100
	void play();
	void stop();

private:
	Mix_Chunk* sound = nullptr;
};

namespace MusicPlayer
{
	void Play(Mix_Music* music);
	void PlayWithIntro(Mix_Music* music, Mix_Music* intro);

	void Pause();
	void Resume();

	void Stop();

	void SetVolume(float volume); // from 0 to 100
	float GetVolume(float volume); // from 0 to 100

	//TODO: Wrap Mix_FadeInMusic() and Mix_FadeOutMusic()
}
