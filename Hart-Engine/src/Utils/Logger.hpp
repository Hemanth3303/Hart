/*
 * Logging functions with different severity levels
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
		Undefined = -1,
		Trace = 0,
		Info,
		Warning,
		Error,
		Fatal
	};

	// if a new engine subsystem is added, add it here and extend LogSourceToString() to return correct string
	enum class LogSource {
		Unknown = -1,

		EngineCore = 0,
		EngineGraphics,
		EngineMaths,
		EnginePlatform,
		EngineUtils,
		EngineAssertion,

		Client,
		ClientAssertion,
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
				case LogSeverity::Undefined:
				default:
					return "::UNDEFINED_SEVERITY";
			}
		}

		static constexpr std::string_view LogSourceToString(LogSource logSource) {
			switch (logSource) {
				case LogSource::EngineCore:
					return "HART::ENGINE::CORE";
				case LogSource::EngineGraphics:
					return "HART::ENGINE::GRAPHICS";
				case LogSource::EngineMaths:
					return "HART::ENGINE::MATHS";
				case LogSource::EnginePlatform:
					return "HART::ENGINE::PLATFORM";
				case LogSource::EngineUtils:
					return "HART::ENGINE::UTILS";
				case LogSource::EngineAssertion:
					return "HART::ENGINE::ASSERTION";
				case LogSource::Client:
					return "HART::CLIENT";
				case LogSource::ClientAssertion:
					return "HART::CLIENT::ASSERTION";
				default:
					return "UNKNOWN_LOG_SOURCE";
			}
		}

	private:
		inline static std::mutex s_LoggerMutex;
	};
}

#if defined(HART_ENGINE_DEBUG_BUILD) || defined(HART_ENGINE_PROFILE_BUILD)
	#define HART_ENGINE_TRACE(source, message, ...)                \
		Hart::Logger::LogMessage(source, Hart::LogSeverity::Trace, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_ENGINE_INFO(source, message, ...)                \
		Hart::Logger::LogMessage(source, Hart::LogSeverity::Info, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_ENGINE_WARNING(source, message, ...)                \
		Hart::Logger::LogMessage(source, Hart::LogSeverity::Warning, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_ENGINE_ERROR(source, message, ...)                \
		Hart::Logger::LogMessage(source, Hart::LogSeverity::Error, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_ENGINE_FATAL(source, message, ...)                \
		Hart::Logger::LogMessage(source, Hart::LogSeverity::Fatal, \
								 message __VA_OPT__(, __VA_ARGS__))

#else
	#define HART_ENGINE_TRACE(source, message, ...)
	#define HART_ENGINE_INFO(source, message, ...)
	#define HART_ENGINE_WARNING(source, message, ...)
	#define HART_ENGINE_ERROR(source, message, ...)
	#define HART_ENGINE_FATAL(source, message, ...)
#endif

#if defined(HART_CLIENT_DEBUG_BUILD) || defined(HART_CLIENT_PROFILE_BUILD)
	#define HART_CLIENT_TRACE(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::Client, Hart::LogSeverity::Trace, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_CLIENT_INFO(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::Client, Hart::LogSeverity::Info, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_CLIENT_WARNING(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::Client, Hart::LogSeverity::Warning, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_CLIENT_ERROR(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::Client, Hart::LogSeverity::Error, \
								 message __VA_OPT__(, __VA_ARGS__))

	#define HART_CLIENT_FATAL(message, ...)                                             \
		Hart::Logger::LogMessage(Hart::LogSource::Client, Hart::LogSeverity::Fatal, \
								 message __VA_OPT__(, __VA_ARGS__))
#else
	#define HART_CLIENT_TRACE(message, ...)
	#define HART_CLIENT_INFO(message, ...)
	#define HART_CLIENT_WARNING(message, ...)
	#define HART_CLIENT_ERROR(message, ...)
	#define HART_CLIENT_FATAL(message, ...)
#endif
