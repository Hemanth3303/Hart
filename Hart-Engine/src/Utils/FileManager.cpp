#include "HartPch.hpp"
#include "FileManager.hpp"

namespace Hart {
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

			HART_ASSERT(inFile.is_open(), "Reason: Couldn't open file");

			dataStream << inFile.rdbuf();

			outDataStr = dataStream.str();

			inFile.close();
		}
		return outDataStr;
	}

	std::vector<void*> FileManager::ReadBinaryFromFile(const std::string& fileName) {
		std::ifstream inFile;
		std::streampos fileSize;
		std::vector<void*> outData = {};
		if (!FileExists(fileName)) {
			HART_ENGINE_ERROR("Could not find file named " + fileName, "\t\t\tIs the file name and/or file path correct?");
		}
		else {
			HART_ENGINE_LOG("Opening file " + fileName);
			inFile.open(fileName, std::ios::binary);
			HART_ASSERT(inFile.is_open(), "Reason: Couldn't open file");

			fileSize = GetFileSizeInBytes(fileName);

			outData.resize(fileSize);
			inFile.read(reinterpret_cast<char*>(&outData[0]), fileSize);
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

		HART_ASSERT(outFile.is_open());
		outFile << data << "\n";
		outFile.close();
	}

	bool FileManager::FileExists(const std::string& fileName) {
		return std::filesystem::exists(fileName);
	}

    std::uintmax_t FileManager::GetFileSizeInBytes(const std::string& filepath) {
		if (FileExists(filepath)) {
			std::filesystem::path path = filepath;
			return std::filesystem::file_size(filepath);
		}
		else {
			HART_ENGINE_ERROR(filepath + " not found");
		}
		return 0;
    }

	std::string FileManager::GetFileName(const std::string& filePath) {
		std::size_t lastSlash = filePath.find_last_of("/\\");
		if (lastSlash == std::string::npos) {
			lastSlash = 0;
		}
		else {
			lastSlash += 1;
		}

		std::size_t lastDot = filePath.rfind('.');
		if (lastDot == std::string::npos) {
			lastDot = filePath.size() - lastSlash;
		}
		else {
			lastDot -= lastSlash;
		}

		return filePath.substr(lastSlash, lastDot);
	}

	std::string FileManager::GetFileNameWithExtension(const std::string& filePath) {
        std::size_t lastSlash = filePath.find_last_of("/\\");
		if (lastSlash == std::string::npos) {
			lastSlash = 0;
		}
		else {
			lastSlash += 1;
		}

		std::size_t end = filePath.length();
		end -= lastSlash;

		return filePath.substr(lastSlash, end);
    }
}
