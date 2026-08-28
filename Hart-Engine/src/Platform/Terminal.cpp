#include "HartPch.hpp"
#include "Terminal.hpp"

#if defined(HART_ENGINE_PLATFORM_WINDOWS)
	#include <windows.h>
#else
	#include <unistd.h>

	#include <cstdio>
	#include <cstring>
	#include <cstdlib>
#endif

namespace Hart {
	bool Terminal::CanStderrUseTerminalColors() {
		// following: https://no-color.org/
		const char* noColor = std::getenv("NO_COLOR");
		if (noColor != nullptr && noColor[0] != '\0') {
			return false;
		}

#if defined(HART_ENGINE_PLATFORM_WINDOWS)
		HANDLE stderrHandle = GetStdHandle(STD_ERROR_HANDLE);
		if (stderrHandle == INVALID_HANDLE_VALUE || stderrHandle == nullptr) {
			return false;
		}

		DWORD stderrMode;
		if (!GetConsoleMode(stderrHandle, &stderrMode)) {
			return false;
		}

		// if VT is not enabled, try to enable it, if that fails, return false
		if (!(stderrMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
			if (!SetConsoleMode(stderrHandle, stderrMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
				return false;
			}
		}

		return true;
#else
		if (!isatty(fileno(stderr))) {
			return false;
		}

		const char* term = std::getenv("TERM");
		if (term == nullptr || term[0] == '\0') {
			return false;
		}

		if (std::strcmp(term, "dumb") == 0) {
			return false;
		}

		return true;
#endif
	}
}
