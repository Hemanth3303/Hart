/*
 * Logging functions with different severity levels and colored output
 */

#pragma once

#include <concepts>
#include <iostream>

namespace Hart {
	template <typename T>
	concept OStreamWritable = requires(std::ostream& os, const T& value) {
		{ os << value } -> std::same_as<std::ostream&>;
	};

	// logs to std::cerr
	class Logger {
	public:
		template <OStreamWritable... T>
		static void LogMessage(const T&... args) {
			(std::cerr << ... << args);
			std::cerr << '\n';
		}
	};
}

// Temp to prevent all the logger missing compile errors
#define HART_ENGINE_TRACE(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
#define HART_ENGINE_LOG(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
#define HART_ENGINE_WARNING(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
#define HART_ENGINE_ERROR(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
#define HART_ENGINE_FATAL(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)

#define HART_CLIENT_TRACE(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
#define HART_CLIENT_LOG(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
#define HART_CLIENT_WARNING(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
#define HART_CLIENT_ERROR(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
#define HART_CLIENT_FATAL(message, ...) Hart::Logger::LogMessage(message, __VA_ARGS__)
