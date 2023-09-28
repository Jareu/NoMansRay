#pragma once
#include "IAudioManager.h"
#include "SDL_mixer.h"
#include <vector>

class SdlMixerAudioManager : public IAudioManager
{
private:
	std::vector<Mix_Chunk*> sounds;
	std::vector<Mix_Music*> music;
	uint32_t volume_;

	void quitMixer();
public:
	SdlMixerAudioManager() = default;
	~SdlMixerAudioManager();

	int32_t loadMusic(const std::string& filename);
	int32_t loadSound(const std::string& filename);
	void setVolume(uint32_t volume);

	AudioError playMusic(uint32_t music_index);
	AudioError playSound(uint32_t sound_index);

	AudioError initMixer() override;

	void toggleMusic();
};