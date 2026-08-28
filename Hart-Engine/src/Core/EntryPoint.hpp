/*
 * Entry point of any Hart Application
 */
#pragma once

#include "Base.hpp"
#include "Application.hpp"

#include <memory>
#include <cstdlib>

#if defined(HART_COMPILER_MSVC)
// refer https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5105
	#pragma warning(disable : 5105)

	#pragma comment(lib, "opengl32")
	#pragma comment(lib, "gdi32")
	#pragma comment(lib, "kernel32")
	#pragma comment(lib, "winmm")
	#pragma comment(lib, "shell32")
	#pragma comment(lib, "user32")

#endif // HART_COMPILER_MSVC

/**
 * Define HART_REQUEST_DGPU_WINDOWS before including this file
 * to request the dedicated gpu on windows, especially in laptops with
 * igpu and dgpu.
 * CMake config for defining HART_CLIENT_PLATFORM_WINDOWS must be setup for this to work.
 */
#if defined(HART_REQUEST_DGPU_WINDOWS) && defined(HART_CLIENT_PLATFORM_WINDOWS)
	#include <windows.h>
extern "C" {
__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

extern std::unique_ptr<Hart::Application> Hart::CreateApplication();

int main(int argc, char** argv) {
	std::unique_ptr<Hart::Application> app = Hart::CreateApplication();

	app->run();

	return EXIT_SUCCESS;
}
