#pragma warning(push, 0)
#pragma warning( disable : 4468 )
#include "SDL.h"
#pragma warning(pop)

#include "SdlMixerAudioManager.h"
#include <iostream>

SdlMixerAudioManager::~SdlMixerAudioManager()
{
	quitMixer();
}

int32_t SdlMixerAudioManager::loadMusic(const std::string& filename)
{
	Mix_Music* music_file = nullptr;
	music_file = Mix_LoadMUS(filename.c_str());
	if (music_file == nullptr) {
		std::cout << "Failed to load music. SDL_Mixer error: " << SDL_GetError() << std::endl;
		return -1;
	}
	music.emplace_back(music_file);
	return music.size() - 1;
}

int32_t SdlMixerAudioManager::loadSound(const std::string& filename)
{
	Mix_Chunk* sound_file = nullptr;
	sound_file = Mix_LoadWAV(filename.c_str());
	if (sound_file == nullptr) {
		std::cout << "Failed to load sound. SDL_Mixer error: " << SDL_GetError() << std::endl;
		return -1;
	}
	sounds.emplace_back(sound_file);
	return sounds.size() - 1;
}

void SdlMixerAudioManager::setVolume(uint32_t volume)
{
	volume_ = (MIX_MAX_VOLUME * volume) / 100;
}

AudioError SdlMixerAudioManager::playMusic(uint32_t music_index)
{
	if (music_index >= music.size()) {
		return AudioError::INDEX_OUT_OF_BOUNDS;
	}

	if (Mix_PlayingMusic() != 0) {
		Mix_HaltMusic();
	}

	Mix_Volume(1, volume_);
	Mix_PlayMusic(music.at(music_index), -1);

	return AudioError::SUCCESS;
}

AudioError SdlMixerAudioManager::playSound(uint32_t sound_index)
{
	if (sound_index >= sounds.size()) {
		return AudioError::INDEX_OUT_OF_BOUNDS;
	}

	Mix_Volume(-1, volume_);
	Mix_PlayChannel(-1, sounds.at(sound_index), 0);

	return AudioError::SUCCESS;
}

AudioError SdlMixerAudioManager::initMixer()
{
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_Mixer could not initialize. Error: " << Mix_GetError() << std::endl;
		return AudioError::INITIALISATION_ERROR;
	}

	setVolume(80);
	return AudioError::SUCCESS;
}

void SdlMixerAudioManager::quitMixer()
{
	for (int s = 0; s < sounds.size(); s++) {
		Mix_FreeChunk(sounds.at(s));
		sounds.at(s) = nullptr;
	}
	for (int m = 0; m < music.size(); m++) {
		Mix_FreeMusic(music.at(m));
		music.at(m) = nullptr;
	}
	Mix_Quit();
}

void SdlMixerAudioManager::toggleMusic()
{
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}
