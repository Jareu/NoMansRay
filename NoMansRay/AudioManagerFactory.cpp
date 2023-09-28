#include "AudioManagerFactory.h"
#include "SdlMixerAudioManager.h"

std::unique_ptr<IAudioManager> AudioManagerFactory::createAudioManager()
{
	auto audio_manager = std::make_unique<SdlMixerAudioManager>();
	return audio_manager;
}