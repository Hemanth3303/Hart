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

	#define HART_DEBUG_ASSERT(expression, ...)

#elif defined(HART_ENGINE_PROFILE_BUILD) || defined(HART_CLIENT_PROFILE_BUILD)
	#define HART_DEBUG_ASSERT(expression, ...)
	#define HART_ENGINE_DEBUG_BREAK()
#else
	#define HART_DEBUG_ASSERT(expression, ...)

	#define HART_ENGINE_DEBUG_BREAK()

#endif
