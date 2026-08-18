#include "HartPch.hpp"
#include "FileManager.hpp"
#include "Core/Assert.hpp"
#include "Utils/Logger.hpp"

#include <fstream>
#include <filesystem>
#include <system_error>
#include <limits>

namespace Hart {
	std::string FileManager::ReadStringFromFile(const std::string& fileName) {
		std::ifstream inFile;
		std::stringstream dataStream;
		std::string outDataStr = "";

		if (!FileExists(fileName)) {
			HART_ENGINE_ERROR("Could not find file named ", fileName, "\n\t\t\tIs the file name and/or file path correct?");
		}
		else {
			HART_ENGINE_LOG("Opening file: ", fileName);
			inFile.open(fileName, std::ios::in);

			HART_DEBUG_ASSERT(inFile.is_open(), "Reason: Couldn't open file");

			dataStream << inFile.rdbuf();

			outDataStr = dataStream.str();

			inFile.close();
		}
		return outDataStr;
	}

	std::vector<std::byte> FileManager::ReadBinaryFromFile(const std::string& fileName) {
		std::ifstream inFile;
		std::vector<std::byte> outData = {};
		if (!FileExists(fileName)) {
			HART_ENGINE_ERROR("Could not find file named ", fileName, "\n\t\t\tIs the file name and/or file path correct?");
		}
		else {
			HART_ENGINE_LOG("Opening file ", fileName);
			inFile.open(fileName, std::ios::binary);
			HART_DEBUG_ASSERT(inFile.is_open(), "Reason: Couldn't open file");

			const uintmax_t fileSize = GetFileSizeInBytes(fileName);
			HART_DEBUG_ASSERT(
				(fileSize <= std::numeric_limits<std::size_t>::max()),
				"File is too large to fit in memory");

			outData.resize(static_cast<std::size_t>(fileSize));
			if (!outData.empty()) {
				inFile.read(
					reinterpret_cast<char*>(outData.data()),
					static_cast<std::streamsize>(outData.size()));
			}
		}

		return outData;
	}

	void FileManager::WriteStringToFile(const std::string& data, const std::string& fileName, const std::string& directory) {
		std::fstream outFile;

		if (!std::filesystem::is_directory(directory)) {
			HART_ENGINE_LOG("Directory ", directory, " doesn't exist. Creating it");
			std::filesystem::create_directories(directory);
		}

		std::string outFileName = directory + std::string("/") + fileName;

		outFile.open(outFileName, std::ios::out | std::ios::app);

		HART_ENGINE_LOG("Writing to file " , outFileName);

		HART_DEBUG_ASSERT(outFile.is_open());
		outFile << data << "\n";
		outFile.close();
	}

	bool FileManager::FileExists(const std::string& fileName) {
		return std::filesystem::exists(fileName);
	}

	uintmax_t FileManager::GetFileSizeInBytes(const std::string& filepath) {
		if (!FileExists(filepath)) {
			HART_ENGINE_ERROR(filepath, " not found");
			return 0;
		}

		std::error_code errorCode;
		uintmax_t fileSize = std::filesystem::file_size(filepath, errorCode);

		if (errorCode) {
			HART_ENGINE_ERROR(filepath, " could not determine file size\n", errorCode.message());
			return 0;
		}

		return fileSize;
	}

	std::string FileManager::GetFileName(const std::string& filePath) {
		size_t lastSlash = filePath.find_last_of("/\\");
		if (lastSlash == std::string::npos) {
			lastSlash = 0;
		}
		else {
			lastSlash += 1;
		}

		size_t lastDot = filePath.rfind('.');
		if (lastDot == std::string::npos) {
			lastDot = filePath.size() - lastSlash;
		}
		else {
			lastDot -= lastSlash;
		}

		return filePath.substr(lastSlash, lastDot);
	}

	std::string FileManager::GetFileNameWithExtension(const std::string& filePath) {
		size_t lastSlash = filePath.find_last_of("/\\");
		if (lastSlash == std::string::npos) {
			lastSlash = 0;
		}
		else {
			lastSlash += 1;
		}

		size_t end = filePath.length();
		end -= lastSlash;

		return filePath.substr(lastSlash, end);
	}
}
