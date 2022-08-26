#pragma once

#include "Core/HartPch.hpp"

namespace Hart {
	namespace Utils {
		class FileManager {
		public:
			//read all data from text file as an std::string, including newlines
			static std::string ReadFromFile(const std::string& fileName);
			//appends an std::string to a file, creating a new file if file doesn't exist
			static void WriteToFile(const std::string& fileName, const std::string& content);
		};
	}
}