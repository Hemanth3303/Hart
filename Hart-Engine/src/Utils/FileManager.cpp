#include "HartPch.hpp"
#include "FileManager.hpp"

namespace Hart {
	namespace Utils {
		std::string FileManager::ReadFromFile(const std::string& fileName) {
			std::ifstream inFile;
			std::stringstream data;

			if (!FileExists(fileName)) {
				//TODO: log failed to open file
			}
			else {
				inFile.open(fileName, std::ios::in);

				HART_ASSERT(inFile);

				data << inFile.rdbuf();

				return data.str();

				inFile.close();
			}

		}

		void FileManager::WriteToFile(const std::string& data, const std::string& fileName, const std::string& directory) {
			std::fstream outFile;
			
			if (!std::filesystem::is_directory(directory)) {
				std::filesystem::create_directories(directory);
			}

			std::string outFileName = directory + std::string("/") + fileName;

			outFile.open(outFileName, std::ios::out | std::ios::app);
			
			HART_ASSERT(outFile);
			outFile << data << "\n";
			outFile.close();
		}

		bool FileManager::FileExists(const std::string& fileName) {
			return std::filesystem::exists(fileName);
		}
	}
}