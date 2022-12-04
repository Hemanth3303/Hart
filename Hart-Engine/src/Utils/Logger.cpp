#include "HartPch.hpp"
#include "Logger.hpp"

#ifdef HART_WINDOWS
#include <Windows.h>
#endif // HART_WINDOWS

namespace Hart {
	namespace Utils {

	#if defined(_WIN32) || defined(_WIN64)
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		#define TEXT_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
		#define TEXT_GREEN (FOREGROUND_GREEN)
		#define TEXT_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
		#define TEXT_RED (FOREGROUND_RED)

		#define SET_TEXT_COLOR(color) SetConsoleTextAttribute(hConsole, color)

	#else
		#define TEXT_WHITE 
		#define TEXT_GREEN 
		#define TEXT_YELLOW 
		#define TEXT_RED 

		#define SET_TEXT_COLOR(color) 

	#endif // if os is windows 

		void Logger::LogMessage(const Loggable& message, const LogSeverity& logSeverity, bool fromEngine) {
			switch (logSeverity) {
			case LogSeverity::Trace:
				SET_TEXT_COLOR(TEXT_GREEN);
				if (fromEngine) {
					EngineTrace(message);
				}
				else {
					ClientTrace(message);
				}
				SET_TEXT_COLOR(TEXT_WHITE);
				break;
			case LogSeverity::Info:
				SET_TEXT_COLOR(TEXT_GREEN);
				if (fromEngine) {
					EngineInfo(message);
				}
				else {
					ClientInfo(message);
				}
				SET_TEXT_COLOR(TEXT_WHITE);
				break;
			case LogSeverity::Warning:
				SET_TEXT_COLOR(TEXT_YELLOW);
				if (fromEngine) {
					EngineWarning(message);
				}
				else {
					ClientWarning(message);
				}
				SET_TEXT_COLOR(TEXT_WHITE);
				break;
			case LogSeverity::Error:
				SET_TEXT_COLOR(TEXT_RED);
				if (fromEngine) {
					EngineError(message);
				}
				else {
					ClientError(message);
				}
				SET_TEXT_COLOR(TEXT_WHITE);
				break;
			case LogSeverity::Fatal:
				SET_TEXT_COLOR(TEXT_RED);
				if (fromEngine) {
					EngineFatal(message);
				}
				else {
					ClientFatal(message);
				}
				SET_TEXT_COLOR(TEXT_WHITE);
				break;
			default:
				if (fromEngine) {
					EngineError("Not a valid log severity");
				}
				else {
					ClientError("Not a valid log severity");
				}
				SET_TEXT_COLOR(TEXT_WHITE);
				break;
			}
		}

		void Logger::EngineTrace(const Loggable& message) {
			std::cout << GREEN << "HART_ENGINE_TRACE: " << message << WHITE << "\n";
		}

		void Logger::EngineInfo(const Loggable& message) {
			std::cout << GREEN << "HART_ENGINE_INFO: " << message << WHITE << "\n";
		}

		void Logger::EngineWarning(const Loggable& message) {
			std::cout << YELLOW << "HART_ENGINE_WARNING: " << message << WHITE << "\n";
		}

		void Logger::EngineError(const Loggable& message) {
			std::cout << RED << "HART_ENGINE_ERROR: " << message << WHITE << "\n";
		}

		void Logger::EngineFatal(const Loggable& message) {
			std::cout << RED << "HART_ENGINE_FATAL: " << message << WHITE << "\n";
		}

		void Logger::ClientTrace(const Loggable& message) {
			std::cout << GREEN << "HART_CLIENT_TRACE: " << message << WHITE << "\n";
		}

		void Logger::ClientInfo(const Loggable& message) {
			std::cout << GREEN << "HART_CLIENT_INFO: " << message << WHITE << "\n";
		}

		void Logger::ClientWarning(const Loggable& message) {
			std::cout << YELLOW << "HART_CLIENT_WARNING: " << message << WHITE << "\n";
		}

		void Logger::ClientError(const Loggable& message) {
			std::cout << RED << "HART_CLIENT_ERROR: " << message << WHITE << "\n";
		}

		void Logger::ClientFatal(const Loggable& message) {
			std::cout << RED << "HART_CLIENT_FATAL: " << message << WHITE << "\n";
		}
	}
}