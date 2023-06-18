#include "HartPch.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

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

		void Logger::LogMessageList(std::initializer_list<Loggable> LogMessageList, const LogSeverity& logSeverity, bool fromEngine) {
			switch (logSeverity) {
				case LogSeverity::Trace:
					SET_TEXT_COLOR(TEXT_WHITE);
					if (fromEngine) {
						EngineTrace(LogMessageList);
					}
					else {
						ClientTrace(LogMessageList);
					}
					SET_TEXT_COLOR(TEXT_WHITE);
					break;
				case LogSeverity::Log:
					SET_TEXT_COLOR(TEXT_GREEN);
					if (fromEngine) {
						EngineLog(LogMessageList);
					}
					else {
						ClientLog(LogMessageList);
					}
					SET_TEXT_COLOR(TEXT_WHITE);
					break;
				case LogSeverity::Warning:
					SET_TEXT_COLOR(TEXT_YELLOW);
					if (fromEngine) {
						EngineWarning(LogMessageList);
					}
					else {
						ClientWarning(LogMessageList);
					}
					SET_TEXT_COLOR(TEXT_WHITE);
					break;
				case LogSeverity::Error:
					SET_TEXT_COLOR(TEXT_RED);
					if (fromEngine) {
						EngineError(LogMessageList);
					}
					else {
						ClientError(LogMessageList);
					}
					SET_TEXT_COLOR(TEXT_WHITE);
					break;
				case LogSeverity::Fatal:
					SET_TEXT_COLOR(TEXT_RED);
					if (fromEngine) {
						EngineFatal(LogMessageList);
					}
					else {
						ClientFatal(LogMessageList);
					}
					SET_TEXT_COLOR(TEXT_WHITE);
					break;
				default:
					if (fromEngine) {
						EngineError({ "Not a valid log severity" });
					}
					else {
						ClientError({ "Not a valid log severity" });
					}
					SET_TEXT_COLOR(TEXT_WHITE);
					break;
			}
		}

		void Logger::EngineTrace(std::initializer_list<Loggable> LogMessageList) {
			std::cout << WHITE;
			LogTimeStamp();
			std::cout << "HART_ENGINE_TRACE: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::EngineLog(std::initializer_list<Loggable> LogMessageList) {
			std::cout << GREEN;
			LogTimeStamp();
			std::cout << "HART_ENGINE_LOG: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::EngineWarning(std::initializer_list<Loggable> LogMessageList) {
			std::cout << YELLOW;
			LogTimeStamp();
			std::cout << "HART_ENGINE_WARNING: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::EngineError(std::initializer_list<Loggable> LogMessageList) {
			std::cout << RED;
			LogTimeStamp();
			std::cout << "HART_ENGINE_ERROR: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::EngineFatal(std::initializer_list<Loggable> LogMessageList) {
			std::cout << RED;
			LogTimeStamp();
			std::cout << "HART_ENGINE_FATAL: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::ClientTrace(std::initializer_list<Loggable> LogMessageList) {
			std::cout << WHITE;
			LogTimeStamp();
			std::cout << "HART_CLIENT_TRACE: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::ClientLog(std::initializer_list<Loggable> LogMessageList) {
			std::cout << GREEN;
			LogTimeStamp();
			std::cout << "HART_CLIENT_LOG: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";;
		}

		void Logger::ClientWarning(std::initializer_list<Loggable> LogMessageList) {
			std::cout << YELLOW;
			LogTimeStamp();
			std::cout << "HART_CLIENT_WARNING: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::ClientError(std::initializer_list<Loggable> LogMessageList) {
			std::cout << RED;
			LogTimeStamp();
			std::cout << "HART_CLIENT_ERROR: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::ClientFatal(std::initializer_list<Loggable> LogMessageList) {
			std::cout << RED;
			LogTimeStamp();
			std::cout << "HART_CLIENT_FATAL: ";
			LogMessagesFromList(LogMessageList);
			std::cout << WHITE << "\n";
		}

		void Logger::LogMessagesFromList(std::initializer_list<Loggable> messageList) {
			std::size_t length = messageList.size();
			const Loggable* messagePtr = messageList.begin();
			for (std::size_t i = 0; i < length; i++) {
				std::cout << *messagePtr;
				messagePtr++;
				// new line not printed for last message
				if (i != length - 1) {
					std::cout << "\n";
				}
			}
		}
		void Logger::LogTimeStamp() {
			std::cout << "[" << Timer::GetCurrentTimeStamp() << "] ";
		}
	}
}