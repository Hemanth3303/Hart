#pragma once

#include "HartPch.hpp"

#include "miniaudio.h"

namespace Hart {
	struct DecoderInfo {
	public:
		DecoderInfo(ma_decoder* p_decoder, bool p_isAtEnd)
			: decoder(p_decoder), isAtEnd(p_isAtEnd) {

		}
	public:
		ma_decoder* decoder = nullptr;
		bool isAtEnd = MA_TRUE;
	};

	struct AudioManagerData {
	public:
		ma_device device;
		ma_device_config deviceConfig;

		static constexpr ma_format SAMPLE_FORMAT = ma_format_f32;
		static constexpr std::uint32_t CHANNEL_COUNT = 2;
		static constexpr std::uint32_t SAMPLE_RATE = 48'000;

		std::vector<DecoderInfo> audioDecoders;
	};
}