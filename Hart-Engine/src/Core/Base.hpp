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
	#define HART_COMPILATION_TIMESTAMP __DATE__ " at " __TIME__

	#if defined(HART_ENGINE_PLATFORM_WINDOWS)
		#define HART_PLATFORM_STR "Windows"
	#elif defined(HART_ENGINE_PLATFORM_LINUX)
		#define HART_PLATFORM_STR "Linux"
	#elif defined(HART_ENGINE_PLATFORM_DARWIN)
		#define HART_PLATFORM_STR "MacOS"
	#else
		#define HART_PLATFORM_STR "Unknown"
	#endif // platform check

	#if defined(HART_ENGINE_ARCHITECTURE_X86_32)
		#define HART_ARCHITECTURE_STR "x86-32"
	#elif defined(HART_ENGINE_ARCHITECTURE_X86_64)
		#define HART_ARCHITECTURE_STR "x86-64"
	#elif defined(HART_ENGINE_ARCHITECTURE_AARCH32)
		#define HART_ARCHITECTURE_STR "aarch32"
	#elif defined(HART_ENGINE_ARCHITECTURE_AARCH64)
		#define HART_ARCHITECTURE_STR "aarch64"
	#elif defined(HART_ENGINE_ARCHITECTURE_RISCV32)
		#define HART_ARCHITECTURE_STR "riscv32"
	#elif defined(HART_ENGINE_ARCHITECTURE_RISCV64)
		#define HART_ARCHITECTURE_STR "riscv64"
	#else
		#define HART_ARCHITECTURE_STR "Unkown"
	#endif // architecture check

	// compiler information
	#if defined(__clang__) // clang needs to be checked for first because for some reason _MS_VER seems to defined when using clang on windows
		#define HART_COMPILER_LLVM_CLANG
		#define HART_COMPILER_STR "LLVM Clang"
		#define HART_COMPILER_VERSION_STR __clang_version__
	#elif defined(_MSC_VER)
		#define HART_COMPILER_MSVC
		#define HART_COMPILER_STR "Microsoft Visual C++ Compiler(MSVC)"
		#define HART_COMPILER_VERSION_STR HART_TO_STR(_MSC_FULL_VER)
	#elif defined(__MINGW64__)
		#define HART_COMPILER_MINGW_W64
		#define HART_COMPILER_STR "MinGW-w64 GCC"
		#define HART_COMPILER_VERSION_STR        \
			HART_TO_STR(__MINGW64_VERSION_MAJOR) \
			"." HART_TO_STR(__MINGW64_VERSION_MINOR)
	#elif defined(__MINGW32__)
		#define HART_COMPILER_MINGW32
		#define HART_COMPILER_STR "MinGW GCC"
		#define HART_COMPILER_VERSION_STR        \
			HART_TO_STR(__MINGW32_VERSION_MAJOR) \
			"." HART_TO_STR(__MINGW32_VERSION_MINOR)
	#elif defined(__GNUC__)
		#define HART_COMPILER_GNU_GCC
		#define HART_COMPILER_STR "GNU GCC"
		#if defined(__GNUC_PATCHLEVEL__)
			#define HART_COMPILER_VERSION_STR \
				HART_TO_STR(__GNUC__)         \
				"." HART_TO_STR(__GNUC_MINOR__) "." HART_TO_STR(__GNUC_PATCHLEVEL__)
		#else
			#define HART_COMPILER_VERSION_STR \
				HART_TO_STR(__GNUC__)         \
				"." HART_TO_STR(__GNUC_MINOR__)
		#endif
	#else
		#define HART_COMPILER_UNKNOWN
		#define HART_COMPILER_STR "Unknown"
		#define HART_COMPILER_VERSION_STR "Unknown"
	#endif

#endif
