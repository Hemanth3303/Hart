#include "Core/HartPch.hpp"
#include "FileManager.hpp"

namespace Hart {
	namespace Utils {

		std::string FileManager::ReadFromFile(const std::string& fileName) {
			std::ifstream file(fileName, std::ios::in);
			std::stringstream fileStream;
			if (file.good()) {
				fileStream << file.rdbuf();
			}
			file.close();
			std::string outString = fileStream.str();
			return outString;
		}

		void FileManager::WriteToFile(const std::string& fileName, const std::string& content) {
			std::ofstream file(fileName, std::ios::out | std::ios::app);
			file << content;
			file.close();
		}

	}
}