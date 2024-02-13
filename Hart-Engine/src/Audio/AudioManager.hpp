#pragma once

#include "HartPch.hpp"
#include "Sound.hpp"
#include "Music.hpp"

#include "miniaudio.h"

namespace Hart {
	class AudioManager {
	public:
		static void Init();
		static void Deinit();

		static void PlaySound(const std::shared_ptr<Sound>& sound);
		static void PlayMusic(const std::shared_ptr<Music>& music);
		static void StopAllAudio();

	private:
		friend void dataCallback(ma_device* device, void* output, const void* input, std::uint32_t frameCount);
		friend std::uint32_t readAndMixPCMFramesF32(ma_decoder* decoder, float* outputF32, std::uint32_t frameCount);
		static bool AreAllDecodersAtEnd();
	};
}