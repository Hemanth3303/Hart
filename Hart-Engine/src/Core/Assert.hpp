/*
 * Custom assert macros.
 * On assertion failure:
 *	- crashes in debug builds.
 *	- just logs in profile builds.
 * Completely stripped in release builds
 */

#pragma once

#include "Utils/Logger.hpp"

#include <string>

#ifdef HART_ENGINE
	#define ASSERT_SOURCE true
#else
	#define ASSERT_SOURCE false
#endif // HART_ENGINE

#if defined(HART_ENGINE_DEBUG_BUILD) || defined(HART_CLIENT_DEBUG_BUILD)

	#if defined(HART_ENGINE_PLATFORM_WINDOWS)
		#include <intrin.h>
		#define HART_ENGINE_DEBUG_BREAK() __debugbreak()
	#elif defined(HART_ENGINE_PLATFORM_LINUX)
		#include <signal.h>
		#define HART_ENGINE_DEBUG_BREAK() raise(SIGTRAP)
	#else
		#define HART_ENGINE_DEBUG_BREAK()
	#endif

	#define HART_ASSERT(expression, ...)                                   \
		do {                                                               \
			auto hartEngineAssertionResult = expression;                   \
			if (!hartEngineAssertionResult) {                              \
				Hart::Logger::LogMessageList(                              \
					{ std::string("Assertion failed: "),                   \
					  std::string("In File: ") + std::string(__FILE__),    \
					  std::string("At Line: ") + std::to_string(__LINE__), \
					  __VA_ARGS__ },                                       \
					Hart::LogSeverity::Fatal,                              \
					ASSERT_SOURCE);                                        \
				HART_ENGINE_DEBUG_BREAK();                           \
			}                                                              \
		} while (0)

	#define HART_ASSERT_EQUAL(expression, value, ...) HART_ASSERT(((expression) == value), __VA_ARGS__)
	#define HART_ASSERT_NOT_EQUAL(expression, value, ...) HART_ASSERT(((expression) != value), __VA_ARGS__)

#elif defined(HART_ENGINE_PROFILE_BUILD) || defined(HART_CLIENT_PROFILE_BUILD)
	#define HART_ASSERT(expression, ...)                                   \
		do {                                                               \
			auto hartEngineAssertionResult = expression;                   \
			if (!hartEngineAssertionResult) {                              \
				Hart::Logger::LogMessageList(                              \
					{ std::string("Assertion failed: "),                   \
					  std::string("In File: ") + std::string(__FILE__),    \
					  std::string("At Line: ") + std::to_string(__LINE__), \
					  __VA_ARGS__ },                                       \
					Hart::LogSeverity::Error,                              \
					ASSERT_SOURCE);                                        \
			}                                                              \
		} while (0)

	#define HART_ASSERT_EQUAL(expression, value, ...) HART_ASSERT(((expression) == value), __VA_ARGS__)
	#define HART_ASSERT_NOT_EQUAL(expression, value, ...) HART_ASSERT(((expression) != value), __VA_ARGS__)

	#define HART_ENGINE_DEBUG_BREAK()
#else
	#define HART_ASSERT(expression, ...)

	#define HART_ASSERT_EQUAL(expression, value, ...)
	#define HART_ASSERT_NOT_EQUAL(expression, value, ...)

	#define HART_ENGINE_DEBUG_BREAK()

#endif
