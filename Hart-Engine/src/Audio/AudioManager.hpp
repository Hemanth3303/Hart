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
		static void StopAllMusic();

	private:
		static ma_device s_Device;
		static ma_device_config s_Config;
	};
}