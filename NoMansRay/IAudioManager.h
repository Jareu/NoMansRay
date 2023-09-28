#pragma once

#include <string>

enum class AudioError
{
	SUCCESS,
	INDEX_OUT_OF_BOUNDS,
	INITIALISATION_ERROR
};

class IAudioManager
{
public:
	virtual int32_t loadMusic(const std::string& filename) = 0;
	virtual int32_t loadSound(const std::string& filename) = 0;
	virtual void setVolume(uint32_t volume) = 0;

	virtual AudioError playMusic(uint32_t music_index) = 0;
	virtual AudioError playSound(uint32_t sound_index) = 0;

	virtual AudioError initMixer() = 0;
	virtual void quitMixer() = 0;

	virtual void toggleMusic() = 0;
};