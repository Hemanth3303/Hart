/*
 * Custom assert macros.
 * On assertion failure:
 *	- debugger breakpoint in debug builds.
 *	- logs a fatal log in profile builds.
 * 	- nop in release builds
 */

#pragma once

#include "Base.hpp"
#include "Utils/Logger.hpp"

#include <string>
#include <cstdlib>

#if defined(HART_ENGINE)
	#define ASSERTION_SOURCE Hart::LogSource::HartEngine
#elif defined(HART_CLIENT)
	#define ASSERTION_SOURCE Hart::LogSource::HartClient
#else
	#define ASSERTION_SOURCE Hart::LogSource::Unknown
#endif // HART_ENGINE

// mainly for other systems to call an unconditional abort on unrecoverable critical invariant failure
#define HART_ENGINE_ABORT() std::abort()

#if defined(HART_ENGINE_PLATFORM_WINDOWS)
	#include <intrin.h>
	#define HART_ENGINE_DEBUG_BREAK() __debugbreak()
#elif defined(HART_ENGINE_PLATFORM_LINUX)
	#include <signal.h>
	#define HART_ENGINE_DEBUG_BREAK() raise(SIGTRAP)
#else
	#define HART_ENGINE_DEBUG_BREAK()
#endif

#if defined(HART_ENGINE_DEBUG_BUILD) || defined(HART_CLIENT_DEBUG_BUILD)

	#define HART_DEBUG_ASSERT(expression, ...)                                                     \
		do {                                                                                       \
			auto hartAssertionResult = expression;                                                 \
			if (!hartAssertionResult) {                                                            \
				Hart::Logger::LogMessage(ASSERTION_SOURCE, Hart::LogSeverity::Fatal,               \
										 "Assertion Failed: ", HART_TO_STR(expression),            \
										 "\nIn file: ", __FILE__,                                  \
										 "\nAt line: ", __LINE__ __VA_OPT__(, "\n", __VA_ARGS__)); \
				HART_ENGINE_DEBUG_BREAK();                                                         \
			}                                                                                      \
		} while (0)
#elif defined(HART_ENGINE_PROFILE_BUILD) || defined(HART_CLIENT_PROFILE_BUILD)
	#define HART_DEBUG_ASSERT(expression, ...)                                                     \
		do {                                                                                       \
			auto hartAssertionResult = expression;                                                 \
			if (!hartAssertionResult) {                                                            \
				Hart::Logger::LogMessage(ASSERTION_SOURCE, Hart::LogSeverity::Fatal,               \
										 "Assertion Failed: ", HART_TO_STR(expression),            \
										 "\nIn file: ", __FILE__,                                  \
										 "\nAt line: ", __LINE__ __VA_OPT__(, "\n", __VA_ARGS__)); \
			}                                                                                      \
		} while (0)
#else
	#define HART_DEBUG_ASSERT(expression, ...)
#endif
