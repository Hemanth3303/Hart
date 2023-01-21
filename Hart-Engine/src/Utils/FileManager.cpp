#include "HartPch.hpp"
#include "FileManager.hpp"

namespace Hart {
	namespace Utils {
		std::string FileManager::ReadFromFile(const std::string& fileName) {
			std::ifstream inFile;
			std::stringstream dataStream;
			std::string outDataStr = "";

			if (!FileExists(fileName)) {
				HART_ENGINE_ERROR("File doesn't exist, is the file path and/or name correct?");
			}
			else {
				std::string info = std::string("Opening file ") + fileName;
				HART_ENGINE_LOG(info)
				inFile.open(fileName, std::ios::in);

				HART_ASSERT(inFile);

				dataStream << inFile.rdbuf();

				outDataStr = dataStream.str();

				inFile.close();
			}
			return outDataStr;
		}

		void FileManager::WriteToFile(const std::string& data, const std::string& fileName, const std::string& directory) {
			std::fstream outFile;
			
			if (!std::filesystem::is_directory(directory)) {
				std::string info = std::string("Directory ") + directory + std::string(" doesn't exist. Creating it");
				HART_ENGINE_LOG(info);
				std::filesystem::create_directories(directory);
			}

			std::string outFileName = directory + std::string("/") + fileName;

			outFile.open(outFileName, std::ios::out | std::ios::app);

			std::string info = std::string("Writing to file ") + outFileName;
			HART_ENGINE_LOG(info);
			
			HART_ASSERT(outFile);
			outFile << data << "\n";
			outFile.close();
		}

		bool FileManager::FileExists(const std::string& fileName) {
			return std::filesystem::exists(fileName);
		}
	}
}