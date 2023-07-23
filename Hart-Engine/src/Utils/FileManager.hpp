/*
* Class that manages all file related activities
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		class FileManager {
		public:
			static std::string ReadStringFromFile(const std::string& fileName);
			static std::vector<std::uint8_t> ReadBinaryFromFile(const std::string& fileName);

			// Writes 'data' to 'fileName', creating the file and/or directories if they don't exist.
			// Also adds a newline character at the end of 'data'
			static void WriteStringToFile(const std::string& data, const std::string& fileName, const std::string& directory = "./");

			static bool FileExists(const std::string& fileName);
		};
	}
}