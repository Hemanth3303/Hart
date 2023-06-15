/*
* Logging functions with differnt severity levels and colored output
* Prefer to use the macros over the class functions
*/

#pragma once

#include "HartPch.hpp"
#include "Loggable.hpp"

namespace Hart {
	namespace Utils {
		enum class LogSeverity {
			Trace = 0,
			Log,
			Warning,
			Error,
			Fatal,
		};

		class Logger {
		public:
			static void LogMessageList(std::initializer_list<Loggable> messageList, const LogSeverity& logSeverity, bool fromEngine);
		private:
			static void EngineTrace(std::initializer_list<Loggable> messageList);
			static void EngineLog(std::initializer_list<Loggable> messageList);
			static void EngineWarning(std::initializer_list<Loggable> messageList);
			static void EngineError(std::initializer_list<Loggable> messageList);
			static void EngineFatal(std::initializer_list<Loggable> messageList);

			static void ClientTrace(std::initializer_list<Loggable> messageList);
			static void ClientLog(std::initializer_list<Loggable> messageList);
			static void ClientWarning(std::initializer_list<Loggable> messageList);
			static void ClientError(std::initializer_list<Loggable> messageList);
			static void ClientFatal(std::initializer_list<Loggable> messageList);

			static void LogMessagesFromList(std::initializer_list<Loggable> messageList);

		};
	}
}

#ifdef HART_ENGINE

	#if !defined(_WIN32) || !defined(_WIN64)
			
		#define WHITE "\033[0m"
		#define RED "\033[31m"
		#define YELLOW "\033[33m"
		#define GREEN "\033[32m"

		#else
			
		#define WHITE ""
		#define RED ""
		#define YELLOW ""
		#define GREEN ""

	#endif //check OS is not windows
#endif // HART_ENGINE

#if defined(HART_DEBUG) || defined(HART_RELEASE)

	#ifdef HART_ENGINE
		
		#define HART_ENGINE_TRACE(message, ...)\
			Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Trace, true)
		#define HART_ENGINE_LOG(message, ...)\
			Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Log, true)
		#define HART_ENGINE_WARNING(message, ...)\
			Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Warning, true)
		#define HART_ENGINE_ERROR(message, ...)\
			Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Error, true)
		#define HART_ENGINE_FATAL(message, ...)\
			Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Fatal, true)

	#endif // HART_ENGINE

	
	#define HART_CLIENT_TRACE(message, ...)\
		Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Trace, false)
	#define HART_CLIENT_LOG(message, ...)\
		Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Log, false)
	#define HART_CLIENT_WARNING(message, ...)\
		Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Warning, false)
	#define HART_CLIENT_ERROR(message, ...)\
		Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Error, false)
	#define HART_CLIENT_FATAL(message, ...)\
		Hart::Utils::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::Utils::LogSeverity::Fatal, false)

#elif defined(HART_DIST)

	#define HART_ENGINE_TRACE(message) 
	#define HART_ENGINE_LOG(message)  
	#define HART_ENGINE_WARNING(message) 
	#define HART_ENGINE_ERROR(message) 
	#define HART_ENGINE_FATAL(message) 

	#define HART_CLIENT_TRACE(message) 
	#define HART_CLIENT_LOG(message)  
	#define HART_CLIENT_WARNING(message) 
	#define HART_CLIENT_ERROR(message) 
	#define HART_CLIENT_FATAL(message) 

#endif // Check build mode
