#pragma once

#if defined(HART_ENGINE_OS_WINDOWS) || defined(HART_CLIENT_OS_WINDOWS)
	// fuck windows
	#if defined(DrawText)
		#undef DrawText
	#endif
	#if defined(near)
		#undef near
	#endif
	#if defined(far)
		#undef far
	#endif

#endif

// helper macros
#define BIT(x) (1u << (x))
#define HART_TO_STR_HELPER(x) #x
#define HART_TO_STR(x) HART_TO_STR_HELPER(x)
