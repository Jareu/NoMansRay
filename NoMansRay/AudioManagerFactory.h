#pragma once
#include "IAudioManager.h"
#include <memory>

class AudioManagerFactory
{
public:
	static std::unique_ptr<IAudioManager> createAudioManager();
};