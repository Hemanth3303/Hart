#pragma once

#include "HartPch.hpp"
#include "Loggable.hpp"

namespace Hart {
	namespace Utils {
		
		enum class LogSeverity {
			Info = 0,
			Warning,
			Error,
		};

		class Logger {
		public:
			static void Log(const Loggable& logMessage, const LogSeverity& severity, bool fromEngine);
		private:
			static void EngineLogInfo(const Loggable& logMessage);
			static void EngineLogWarning(const Loggable& logMessage);
			static void EngineLogError(const Loggable& logMessage);

			static void ClientLogInfo(const Loggable& logMessage);
			static void ClientLogWarning(const Loggable& logMessage);
			static void ClientLogError(const Loggable& logMessage);
		};
	}
}

#if defined(HART_DEBUG) || defined(HART_RELEASE)
#ifdef HART_ENGINE
	#define HART_ENGINE_INFO(x)			Hart::Utils::Logger::Log(x, Hart::Utils::LogSeverity::Info, true)
	#define HART_ENGINE_WARN(x)			Hart::Utils::Logger::Log(x, Hart::Utils::LogSeverity::Warning, true)
	#define HART_ENGINE_ERROR(x)		Hart::Utils::Logger::Log(x, Hart::Utils::LogSeverity::Error, true)
#endif // HART_ENGINE

	#define HART_CLIENT_INFO(x)			Hart::Utils::Logger::Log(x, Hart::Utils::LogSeverity::Info, false)
	#define HART_CLIENT_WARN(x)			Hart::Utils::Logger::Log(x, Hart::Utils::LogSeverity::Warning, false)
	#define HART_CLIENT_ERROR(x)		Hart::Utils::Logger::Log(x, Hart::Utils::LogSeverity::Error, false)
#else
	#define HART_ENGINE_INFO(x)	
	#define HART_ENGINE_WARN(x)	
	#define HART_ENGINE_ERROR(x) 

	#define HART_CLIENT_INFO(x)	
	#define HART_CLIENT_WARN(x)	
	#define HART_CLIENT_ERROR(x) 
#endif //HART_DEBUG OR HART_RELEASE