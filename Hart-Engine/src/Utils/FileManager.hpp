/*
* Class that manages all file related activities
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	class FileManager {
	public:
		static std::string ReadStringFromFile(const std::string& fileName);
		static std::vector<void*> ReadBinaryFromFile(const std::string& fileName);

		// Writes 'data' to 'fileName', creating the file and/or directories if they don't exist.
		// Also adds a newline character at the end of 'data'
		static void WriteStringToFile(const std::string& data, const std::string& fileName, const std::string& directory = "./");

		static bool FileExists(const std::string& fileName);

		// Returns file name without the filepath or extension
		// example: assets/images/grass.png will return grass
		static std::string GetFileName(const std::string& filePath);
		// Returns file name without the filepath but extension is retained
		// example: assets/images/grass.png will return grass.png
		static std::string GetFileNameWithExtension(const std::string& filePath);
	};
}