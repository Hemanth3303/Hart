// SFX files

#pragma once

#include "HartPch.hpp"

namespace Hart {
	class Sound {
	public:
		Sound(const std::string filePath, bool looping = false, std::uint32_t volume = 100);
		~Sound();

		inline const std::string& getFilePath() const { return m_FilePath; }
		inline const bool isLooping() const { return m_Looping; }
	private:
		std::string m_FilePath;
		bool m_Looping;
		std::uint32_t m_Volume;
	};
}