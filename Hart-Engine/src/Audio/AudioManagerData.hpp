#pragma once

#include "HartPch.hpp"

#include "miniaudio.h"

namespace Hart {
	struct AudioManagerData {
	public:
		ma_device device;
		ma_device_config deviceConfig;

		static constexpr std::uint32_t MAX_AUDIO_DECODERS = 1'000;
		std::uint32_t decoderIndex;

		static constexpr ma_format SAMPLE_FORMAT = ma_format_f32;
		static constexpr std::uint32_t CHANNEL_COUNT = 2;
		static constexpr std::uint32_t SAMPLE_RATE = 48'000;

		std::array<ma_decoder*, MAX_AUDIO_DECODERS> decoders;
		std::array<ma_bool32, MAX_AUDIO_DECODERS> decodersAtEnd;
	};
}