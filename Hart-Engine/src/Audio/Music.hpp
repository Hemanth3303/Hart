// Music files

#pragma once

#include "HartPch.hpp"

namespace Hart {
	class Music {
	public:
		Music(const std::string filePath, bool looping = true, std::uint32_t volume = 100);
		~Music();

		inline const std::string& getFilePath() const { return m_FilePath; }
		inline const bool isLooping() const { return m_Looping; }
	private:
		std::string m_FilePath;
		bool m_Looping;
		std::uint32_t m_Volume;
	};
}