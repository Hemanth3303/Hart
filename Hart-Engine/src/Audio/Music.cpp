#include "HartPch.hpp"
#include "Music.hpp"

namespace Hart {
	Music::Music(const std::string filePath) {
		ma_result result;
		result = ma_decoder_init_file(filePath.c_str(), nullptr, &decoder);
		HART_ASSERT_EQUAL(result, MA_SUCCESS, "Failed to load music file");
		ma_data_source_set_looping(&decoder, MA_TRUE);
	}

	Music::~Music() {
		ma_decoder_uninit(&decoder);
	}
}