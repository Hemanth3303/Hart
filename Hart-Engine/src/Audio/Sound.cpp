#include "HartPch.hpp"
#include "Sound.hpp"
#include "AudioManagerData.hpp"

namespace Hart {
	Sound::Sound(const std::string filePath, bool looping, std::uint32_t volume)
		: m_FilePath(filePath), m_Looping(looping), m_Volume(volume) {
	}

	Sound::~Sound() {

	}
}