#include "HartPch.hpp"
#include "Logger.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

namespace Hart {
	namespace Utils {

		//public
		void Logger::Log(const Loggable& logMessage, const LogSeverity& severity, bool fromEngine) {
			switch (severity) {
			case LogSeverity::Info:
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			#endif //_WIN32
				if (fromEngine) {
					EngineLogInfo(logMessage);
				}
				else {
					ClientLogInfo(logMessage);
				}
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			#endif //_WIN32
				break;
			case LogSeverity::Warning:
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			#endif //_WIN32
				if (fromEngine) {
					EngineLogWarning(logMessage);
				}
				else {
					ClientLogWarning(logMessage);
				}
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			#endif //_WIN32
				break;
			case LogSeverity::Error:
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			#endif //_WIN32
				if (fromEngine) {
					EngineLogError(logMessage);
				}
				else {
					ClientLogError(logMessage);
				}
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			#endif //_WIN32
				break;
			default:
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			#endif //_WIN32
				if (fromEngine) {
					EngineLogError("Not a valid severity");
				}
				else {
					ClientLogError("Not a valid severity");
				}
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			#endif //_WIN32
				break;
			}
		}

		//private
		void Logger::EngineLogInfo(const Loggable& logMessage) {
			std::cout << LOGGER_COLOR_GREEN << "HART_ENGINE_INFO: " << logMessage << LOGGER_COLOR_RESET << "\n";
		}

		void Logger::EngineLogWarning(const Loggable& logMessage) {
			std::cout << LOGGER_COLOR_YELLOW << "HART_ENGINE_WARNING: " << logMessage << LOGGER_COLOR_RESET << "\n";
		}

		void Logger::EngineLogError(const Loggable& logMessage) {
			std::cout << LOGGER_COLOR_RED << "HART_ENGINE_ERROR: " << logMessage << LOGGER_COLOR_RESET << "\n";
		}

		void Logger::ClientLogInfo(const Loggable& logMessage) {
			std::cout << LOGGER_COLOR_GREEN << "HART_CLIENT_INFO: " << logMessage << LOGGER_COLOR_RESET << "\n";
		}

		void Logger::ClientLogWarning(const Loggable& logMessage) {
			std::cout << LOGGER_COLOR_YELLOW << "HART_CLIENT_WARNING: " << logMessage << LOGGER_COLOR_RESET << "\n";
		}

		void Logger::ClientLogError(const Loggable& logMessage) {
			std::cout << LOGGER_COLOR_RED << "HART_CLIENT_ERROR: " << logMessage << LOGGER_COLOR_RESET << "\n";
		}

		//private members
	#ifdef _WIN32
		HANDLE Logger::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	#endif //_WIN32
	}
}