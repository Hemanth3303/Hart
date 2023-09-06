/*
* Custom assert macros, stripped in distribution builds
*/

#pragma once

#include "Utils/Logger.hpp"

#include <string>

#ifdef HART_ENGINE
	#define ASSERT_SOURCE true
#else
	#define ASSERT_SOURCE false
#endif // HART_ENGINE

#if defined(HART_DEBUG)

	#if defined(_WIN32) || defined(_WIN64)
		#include <intrin.h>
		#define HART_DEBUG_BREAK() __debugbreak()
	#elif defined(__linux__)
		#include <signal.h>
		#define HART_DEBUG_BREAK() raise(SIGTRAP)
	#else
		#define HART_DEBUG_BREAK()
	#endif

	#define HART_ASSERT(expression, ...) \
		if(!expression) { \
			Hart::Logger::LogMessageList( \
				{ \
					std::string("Assertion failed: "), \
					std::string("In File: ") + std::string(__FILE__), \
					std::string("At Line: ") + std::to_string(__LINE__), \
					__VA_ARGS__ \
				}, \
				Hart::LogSeverity::Fatal, \
				ASSERT_SOURCE \
			); \
			HART_DEBUG_BREAK(); \
		}

	#define HART_ASSERT_EQUAL(expression, value, ...) HART_ASSERT((expression == value), __VA_ARGS__)
	#define HART_ASSERT_NOT_EQUAL(expression, value, ...) HART_ASSERT((expression != value), __VA_ARGS__)

#elif defined(HART_RELEASE)
	#define HART_ASSERT(expression, ...) \
			if(!expression) { \
				Hart::Logger::LogMessageList( \
					{ \
						std::string("Assertion failed: "), \
						std::string("In File: ") + std::string(__FILE__), \
						std::string("At Line: ") + std::to_string(__LINE__), \
						__VA_ARGS__ \
					}, \
					Hart::LogSeverity::Error, \
					ASSERT_SOURCE \
				); \
			}

	#define HART_ASSERT_EQUAL(expression, value, ...) HART_ASSERT((expression == value), __VA_ARGS__)
	#define HART_ASSERT_NOT_EQUAL(expression, value, ...) HART_ASSERT((expression != value), __VA_ARGS__)
#else

	#define HART_ASSERT(expression, ...)
	#define HART_ASSERT_EQUAL(expression, value, ...) 
	#define HART_ASSERT_NOT_EQUAL(expression, value, ...) 

#endif