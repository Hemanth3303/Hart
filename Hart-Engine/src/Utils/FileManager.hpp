#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		class FileManager {
		public:
			
			//Read all data from text file as an std::string, including newlines
			static std::string ReadFromFile(const std::string& fileName);

			//Appends an std::string to a file, creating a new file if file doesn't exist
			//Note: The folder needs to exist
			static void WriteToFile(const std::string& fileName, const std::string& content);

		};
	}
}