// Audio Engine

#pragma once

#include "Sound.hpp"
#include "Music.hpp"

#include "miniaudio.h"

#include <memory>

namespace Hart {
	class AudioManager {
	public:
		static void Init();
		static void DeInit();

		static void PlaySound(const std::shared_ptr<Sound>& sound);
		static void PlayMusic(const std::shared_ptr<Music>& music);
		static void PauseAllAudio();
		static void ResumeAllAudio();

	private:
		static bool AreAllDecodersAtEnd();
		static void ClearDoneDecoders();

		friend void dataCallback(ma_device* device, void* output, const void* input, uint32_t frameCount);
		friend uint32_t readAndMixPCMFramesF32(ma_decoder* decoder, float* outputF32, uint32_t frameCount);
		friend class Application;
	};
}
