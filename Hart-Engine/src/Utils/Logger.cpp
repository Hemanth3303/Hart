#include "HartPch.hpp"
#include "Logger.hpp"

namespace Hart {
	namespace Utils {

		//public
		void Logger::Log(const Loggable& logMessage, const LogSeverity& severity, bool fromEngine) {
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
					ClientLogError(logMessage);
				}
				break;
			default:
				if (fromEngine) {
					EngineLogError("Not a valid severity");
				}
				else {
					ClientLogError("Not a valid severity");
				}
				break;
			}
		}

		//private
		void Logger::EngineLogInfo(const Loggable& logMessage) {
			std::cerr << "HART_ENGINE_INFO: " << logMessage << "\n";
		}

		void Logger::EngineLogWarning(const Loggable& logMessage) {
			std::cerr << "HART_ENGINE_WARNING: " << logMessage << "\n";
		}

		void Logger::EngineLogError(const Loggable& logMessage) {
			std::cerr << "HART_ENGINE_ERROR: " << logMessage << "\n";
		}

		void Logger::ClientLogInfo(const Loggable& logMessage) {
			std::cerr << "HART_CLIENT_INFO: " << logMessage << "\n";
		}

		void Logger::ClientLogWarning(const Loggable& logMessage) {
			std::cerr << "HART_CLIENT_WARNING: " << logMessage << "\n";
		}

		void Logger::ClientLogError(const Loggable& logMessage) {
			std::cerr << "HART_CLIENT_ERROR: " << logMessage << "\n";
		}
		
	}
}