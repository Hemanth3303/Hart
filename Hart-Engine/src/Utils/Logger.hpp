/*
 * Logging functions with different severity levels and colored output
 * Prefer to use the macros over the class functions
 */

#pragma once

#include "Timer.hpp"

#include <concepts>
#include <iostream>
#include <mutex>
#include <string_view>

namespace Hart {
	template <typename T>
	concept OStreamWritable = requires(std::ostream& os, const T& value) {
		{ os << value } -> std::same_as<std::ostream&>;
	};

	enum class LogSeverity {
		Trace = 0,
		Info,
		Warning,
		Error,
		Fatal
	};

	enum class LogSource {
		HartEngine = 0,
		HartClient
	};

	// logs to std::cerr
	class Logger {
	public:
		template <OStreamWritable... T>
		static void LogMessage(const LogSource& logSource, const LogSeverity& severity, const T&... args) {
			std::lock_guard<std::mutex> lock(s_LoggerMutex);
			std::cerr
				<< Timer::GetTimeStampUTC()
				<< " ["
				<< LogSourceToString(logSource)
				<< LogSeverityToString(severity)
				<< "]: ";
			(std::cerr << ... << args);
			std::cerr << '\n';
		}

	private:
		static constexpr std::string_view LogSeverityToString(LogSeverity severity) {
			switch (severity) {
				case LogSeverity::Trace:
					return "::TRACE";
				case LogSeverity::Info:
					return "::INFO";
				case LogSeverity::Warning:
					return "::WARNING";
				case LogSeverity::Error:
					return "::ERROR";
				case LogSeverity::Fatal:
					return "::FATAL";
				default:
					return "::UNDEFINED_SEVERITY";
			}
		}

		static constexpr std::string_view LogSourceToString(LogSource logSource) {
			switch (logSource) {
				case LogSource::HartEngine:
					return "HART_ENGINE";
				case LogSource::HartClient:
					return "HART_CLIENT";
				default:
					return "UNKNOWN_LOG_SOURCE";
			}
		}

	private:
		inline static std::mutex s_LoggerMutex;
	};
}

#if defined(HART_ENGINE_DEBUG_BUILD) || defined(HART_ENGINE_PROFILE_BUILD)
	#define HART_ENGINE_TRACE(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::HartEngine, Hart::LogSeverity::Trace, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_ENGINE_LOG(message, ...)                                              \
		Hart::Logger::LogMessage(Hart::LogSource::HartEngine, Hart::LogSeverity::Info, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_ENGINE_WARNING(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::HartEngine, Hart::LogSeverity::Warning, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_ENGINE_ERROR(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::HartEngine, Hart::LogSeverity::Error, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_ENGINE_FATAL(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::HartEngine, Hart::LogSeverity::Fatal, \
								 message __VA_OPT__(, __VA_ARGS__))

#else
	#define HART_ENGINE_TRACE(message, ...)
	#define HART_ENGINE_LOG(message, ...)
	#define HART_ENGINE_WARNING(message, ...)
	#define HART_ENGINE_ERROR(message, ...)
	#define HART_ENGINE_FATAL(message, ...)
#endif

#if defined(HART_CLIENT_DEBUG_BUILD) || defined(HART_CLIENT_PROFILE_BUILD)
	#define HART_CLIENT_TRACE(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::HartClient, Hart::LogSeverity::Trace, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_CLIENT_LOG(message, ...)                                              \
		Hart::Logger::LogMessage(Hart::LogSource::HartClient, Hart::LogSeverity::Info, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_CLIENT_WARNING(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::HartClient, Hart::LogSeverity::Warning, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_CLIENT_ERROR(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::HartClient, Hart::LogSeverity::Error, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_CLIENT_FATAL(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::HartClient, Hart::LogSeverity::Fatal, \
								 message __VA_OPT__(, __VA_ARGS__))
#else
	#define HART_CLIENT_TRACE(message, ...)
	#define HART_CLIENT_LOG(message, ...)
	#define HART_CLIENT_WARNING(message, ...)
	#define HART_CLIENT_ERROR(message, ...)
	#define HART_CLIENT_FATAL(message, ...)
#endif
