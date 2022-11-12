/*
* Class that manages all file related activities
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		class FileManager {
		public:
			static std::string ReadFromFile(const std::string& fileName);
			// Writes 'data' to 'fileName', creating the file and/or directories if they don't exist.
			// Also adds a newline character at the end of 'data'
			static void WriteToFile(const std::string& data, const std::string& fileName, const std::string& directory = "./");
			// Returns true if file exists, otherwise returns false
			static bool FileExists(const std::string& fileName);
		};
	}
}