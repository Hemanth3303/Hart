#pragma once

// utility macros

#define BIT(x) (1 << x)

// compilation information
#if defined(HART_ENGINE)
	// helper macros
	#define TO_STR_HELPER(x) #x
	#define TO_STR(x) TO_STR_HELPER(x)

	// compilation time information
	#define HART_COMPILATION_TIMESTAMP __DATE__ " at " __TIME__

	// platform information
	#if defined(_WIN32)
		#if defined(_WIN64)
			#define HART_PLATFORM "Windows x86_64"
		#else
			#define HART_PLATFORM "Windows x86"
		#endif
	#elif defined(__linux__)
		#define HART_PLATFORM "Linux"
	#else
		#define HART_PLATFORM "Unknown"
	#endif

	// compiler information
	#if defined(__clang__) // clang needs to be checked for first because for some reason _MS_VER seems to defined when using clang on windows
		#define HART_COMPILER "LLVM Clang"
		#define HART_COMPILER_VERSION __clang_version__
	#elif defined(_MSC_VER)
		#define HART_COMPILER "Microsoft Visual C++ Compiler(MSVC)"
		#define HART_COMPILER_VERSION TO_STR(_MSC_FULL_VER)
	#elif defined(__MINGW64__)
		#define HART_COMPILER "MinGW-w64 GCC"
		#define HART_COMPILER_VERSION TO_STR(__MINGW64_VERSION_MAJOR) "." TO_STR(__MINGW64_VERSION_MINOR)
	#elif defined(__MINGW32__)
		#define HART_COMPILER "MinGW GCC"
		#define HART_COMPILER_VERSION TO_STR(__MINGW32_VERSION_MAJOR) "." TO_STR(__MINGW32_VERSION_MINOR)
	#elif defined(__GNUC__)
		#define HART_COMPILER "GNU GCC"
		#if defined(__GNUC_PATCHLEVEL__)
			#define HART_COMPILER_VERSION TO_STR(__GNUC__) "." TO_STR(__GNUC_MINOR__) "." TO_STR(__GNUC_PATCHLEVEL__)
		#else
			#define HART_COMPILER_VERSION TO_STR(__GNUC__) "." TO_STR(__GNUC_MINOR__)
		#endif
	#else 
		#define HART_COMPILER "Unknown"
		#define HART_COMPILER_VERSION "Unknown"
	#endif

#endif