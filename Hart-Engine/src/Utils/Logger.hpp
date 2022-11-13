#pragma once

#include "HartPch.hpp"
#include "Loggable.hpp"

namespace Hart {
	namespace Utils {

		enum class LogSeverity {
			Trace = 0,
			Info,
			Warning,
			Error,
			Fatal,
		};

		class Logger {
		public:
			static void LogMessage(const Loggable& message, const LogSeverity& logSeverity, bool fromEngine);
		private:
			static void EngineTrace(const Loggable& message);
			static void EngineInfo(const Loggable& message);
			static void EngineWarning(const Loggable& message);
			static void EngineError(const Loggable& message);
			static void EngineFatal(const Loggable& message);

			static void ClientTrace(const Loggable& message);
			static void ClientInfo(const Loggable& message);
			static void ClientWarning(const Loggable& message);
			static void ClientError(const Loggable& message);
			static void ClientFatal(const Loggable& message);

		};

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

		#define HART_ENGINE_TRACE(message) Logger::LogMessage(message, LogSeverity::Trace, true);
		#define HART_ENGINE_INFO(message) Logger::LogMessage(message, LogSeverity::Info, true);
		#define HART_ENGINE_WARNING(message) Logger::LogMessage(message, LogSeverity::Warning, true);
		#define HART_ENGINE_ERROR(message) Logger::LogMessage(message, LogSeverity::Error, true);
		#define HART_ENGINE_FATAL(message) Logger::LogMessage(message, LogSeverity::Fatal, true);

		#define HART_CLIENT_TRACE(message) Logger::LogMessage(message, LogSeverity::Trace, false);
		#define HART_CLIENT_INFO(message) Logger::LogMessage(message, LogSeverity::Info, false);
		#define HART_CLIENT_WARNING(message) Logger::LogMessage(message, LogSeverity::Warning, false);
		#define HART_CLIENT_ERROR(message) Logger::LogMessage(message, LogSeverity::Error, false);
		#define HART_CLIENT_FATAL(message) Logger::LogMessage(message, LogSeverity::Fatal, false);

	#elif defined(HART_DIST)

	#endif // Check build mode

	}
}