#include "HartPch.hpp"
#include "Sound.hpp"
#include "AudioManagerData.hpp"

namespace Hart {
	Sound::Sound(const std::string filePath) {
		ma_result result;

		ma_decoder_config decoderConfig = ma_decoder_config_init(AudioManagerData::SAMPLE_FORMAT, AudioManagerData::CHANNEL_COUNT, AudioManagerData::SAMPLE_RATE);

		result = ma_decoder_init_file(filePath.c_str(),&decoderConfig, &decoder);
		HART_ASSERT_EQUAL(result, MA_SUCCESS, "Failed to load sound file");
		ma_data_source_set_looping(&decoder, MA_FALSE);
	}

	Sound::~Sound() {
		ma_decoder_uninit(&decoder);
	}
}