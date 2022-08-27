#include "Core/HartPch.hpp"
#include "Logger.hpp"

namespace Hart {
	namespace Utils {

		//public
		void Logger::Log(const std::string& logMessage, const LogSeverity& severity, bool fromEngine) {
			switch (severity) {
				case LogSeverity::Info:
					if (fromEngine) {
						EngineLogInfo(logMessage);
					}
					else {
						ClientLogInfo(logMessage);
					}
					break;
				case LogSeverity::Warning:
					if (fromEngine) {
						EngineLogWarning(logMessage);
					}
					else {
						ClientLogWarning(logMessage);
					}
					break;
				case LogSeverity::Error:
					if (fromEngine) {
						EngineLogError(logMessage);
					}
					else {
						ClientLogWarning(logMessage);
					}
					break;
				default:
					if (fromEngine) {
						EngineLogError("Not a valid severity");
					}
					else {
						ClientLogWarning("Not a valid severity");
					}
					break;
			}
		}

		//private
		void Logger::EngineLogInfo(const std::string& logMessage) {
			std::cerr << "HART::ENGINE::INFO: " << logMessage << "\n";
		}

		void Logger::EngineLogWarning(const std::string& logMessage) {
			std::cerr << "HART::ENGINE::WARNING: " << logMessage << "\n";
		}

		void Logger::EngineLogError(const std::string& logMessage) {
			std::cerr << "HART::ENGINE::ERROR: " << logMessage << "\n";
		}

		void Logger::ClientLogInfo(const std::string& logMessage) {
			std::cerr << "HART::CLIENT::INFO: " << logMessage << "\n";
		}

		void Logger::ClientLogWarning(const std::string& logMessage) {
			std::cerr << "HART::CLIENT::WARNING: " << logMessage << "\n";
		}

		void Logger::ClientLogError(const std::string& logMessage) {
			std::cerr << "HART::CLIENT::ERROR: " << logMessage << "\n";
		}
		
	}
}