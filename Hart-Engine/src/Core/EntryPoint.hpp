/*
 * Entry point of any Hart Application
 */

#pragma once

#ifdef _MSC_VER
	#pragma warning(disable : 5105)

	#pragma comment(lib, "opengl32")
	#pragma comment(lib, "gdi32")
	#pragma comment(lib, "kernel32")
	#pragma comment(lib, "winmm")
	#pragma comment(lib, "shell32")
	#pragma comment(lib, "user32")

#endif // _MSC_VER

// #if defined(HART_CLIENT_PLATFORM_WINDOWS) && defined(HART_CLIENT_RELEASE_BUILD)
// #include <windows.h>
// extern "C" {
//	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
// }
// #endif

#include "Application.hpp"

extern std::unique_ptr<Hart::Application> Hart::CreateApplication();

int main(int argc, char** argv) {
	std::unique_ptr<Hart::Application> app = Hart::CreateApplication();

	app->run();

	return 0;
}
