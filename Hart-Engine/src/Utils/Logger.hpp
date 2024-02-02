/*
* Logging functions with differnt severity levels and colored output
* Prefer to use the macros over the class functions
*/

#pragma once

#include "HartPch.hpp"
#include "Loggable.hpp"

namespace Hart {
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
		static void LogTimeStamp();

	};
}

#if defined(HART_DEBUG) || defined(HART_RELEASE) || defined(HART_CLIENT_DEBUG) || defined(HART_CLIENT_RELEASE)

	#if defined(HART_ENGINE)
		
		#define HART_ENGINE_TRACE(message, ...)\
			Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Trace, true)
		#define HART_ENGINE_LOG(message, ...)\
			Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Log, true)
		#define HART_ENGINE_WARNING(message, ...)\
			Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Warning, true)
		#define HART_ENGINE_ERROR(message, ...)\
			Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Error, true)
		#define HART_ENGINE_FATAL(message, ...)\
			Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Fatal, true)

	#elif defined(HART_CLIENT)

	#define HART_CLIENT_TRACE(message, ...)\
		Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Trace, false)
	#define HART_CLIENT_LOG(message, ...)\
		Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Log, false)
	#define HART_CLIENT_WARNING(message, ...)\
		Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Warning, false)
	#define HART_CLIENT_ERROR(message, ...)\
		Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Error, false)
	#define HART_CLIENT_FATAL(message, ...)\
		Hart::Logger::LogMessageList({ message, __VA_ARGS__ }, Hart::LogSeverity::Fatal, false)

	#endif // HART_ENGINE


#elif defined(HART_DIST) || defined(HART_CLIENT_DIST)

	#define HART_ENGINE_TRACE(message, ...) 
	#define HART_ENGINE_LOG(message, ...)  
	#define HART_ENGINE_WARNING(message, ...) 
	#define HART_ENGINE_ERROR(message, ...) 
	#define HART_ENGINE_FATAL(message, ...) 

	#define HART_CLIENT_TRACE(message, ...) 
	#define HART_CLIENT_LOG(message, ...)  
	#define HART_CLIENT_WARNING(message, ...) 
	#define HART_CLIENT_ERROR(message, ...) 
	#define HART_CLIENT_FATAL(message, ...)

#endif // Check build mode
