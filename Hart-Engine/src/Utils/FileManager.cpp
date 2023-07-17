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

		std::vector<std::uint8_t> FileManager::ReadBinaryFile(const std::string& fileName) {
			std::ifstream inFile;
			std::vector<std::uint8_t> outData = {};
			if (!FileExists(fileName)) {
				HART_ENGINE_ERROR("Could not find file named " + fileName, "\t\t\tIs the file name and/or file path correct?");
			}
			else {
				HART_ENGINE_LOG("Opening file " + fileName);
				inFile.open(fileName, std::ios::binary);
				// copies all data into buffer
				outData.assign(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());
			}

			return outData;
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