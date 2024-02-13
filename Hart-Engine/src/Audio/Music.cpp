#include "HartPch.hpp"
#include "Music.hpp"
#include "AudioManagerData.hpp"

namespace Hart {
	Music::Music(const std::string filePath, bool looping, std::uint32_t volume)
		: m_FilePath(filePath), m_Looping(looping), m_Volume(volume) {
	}

	Music::~Music() {

	}
}