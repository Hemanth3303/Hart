#pragma once

#if defined(HART_ENGINE_PLATFORM_WINDOWS) || defined(HART_CLIENT_PLATFORM_WINDOWS)
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
#define BIT(x) (1 << (x))
#define HART_TO_STR_HELPER(x) #x
#define HART_TO_STR(x) HART_TO_STR_HELPER(x)

// compilation information
#if defined(HART_ENGINE)

	// compiler information
	#if defined(__clang__) // clang needs to be checked for first because for some reason _MS_VER seems to defined when using clang on windows
		#define HART_COMPILER_LLVM_CLANG
		#define HART_COMPILER_STR "LLVM Clang"
		#define HART_COMPILER_VERSION_STR __clang_version__
	#elif defined(_MSC_VER)
		#define HART_COMPILER_MSVC
	#elif defined(__MINGW64__)
		#define HART_COMPILER_MINGW_W64
	#elif defined(__MINGW32__)
		#define HART_COMPILER_MINGW32
	#elif defined(__GNUC__)
		#define HART_COMPILER_GNU_GCC
	#else
		#define HART_COMPILER_UNKNOWN
	#endif

#endif
