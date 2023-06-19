#include "HartPch.hpp"
#include "FileManager.hpp"

namespace Hart {
	namespace Utils {
		std::string FileManager::ReadStringFromFile(const std::string& fileName) {
			std::ifstream inFile;
			std::stringstream dataStream;
			std::string outDataStr = "";

			if (!FileExists(fileName)) {
				HART_ENGINE_ERROR("Could not find file named " + fileName, "\t\t\tIs the file name and/or file path correct?");
			}
			else {
				HART_ENGINE_LOG("Opening file " + fileName);
				inFile.open(fileName, std::ios::in);

				HART_ASSERT(inFile);

				dataStream << inFile.rdbuf();

				outDataStr = dataStream.str();

				inFile.close();
			}
			return outDataStr;
		}

		void FileManager::WriteStringToFile(const std::string& data, const std::string& fileName, const std::string& directory) {
			std::fstream outFile;
			
			if (!std::filesystem::is_directory(directory)) {
				HART_ENGINE_LOG("Directory " + directory + " doesn't exist. Creating it");
				std::filesystem::create_directories(directory);
			}

			std::string outFileName = directory + std::string("/") + fileName;

			outFile.open(outFileName, std::ios::out | std::ios::app);

			HART_ENGINE_LOG("Writing to file " + outFileName);
			
			HART_ASSERT(outFile);
			outFile << data << "\n";
			outFile.close();
		}

		bool FileManager::FileExists(const std::string& fileName) {
			return std::filesystem::exists(fileName);
		}
	}
}