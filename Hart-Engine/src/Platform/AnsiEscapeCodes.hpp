#pragma once

#include <string_view>

namespace Hart {
	// ==============format codes============== //

	inline constexpr std::string_view ANSI_RESET = "\x1b[0m";
	inline constexpr std::string_view ANSI_FOREGROUND_RESET = "\x1b[39m"; // default foreground
	inline constexpr std::string_view ANSI_BACKGROUND_RESET = "\x1b[49m"; // default background
	inline constexpr std::string_view ANSI_BOLD = "\x1b[1m";
	inline constexpr std::string_view ANSI_DIM = "\x1b[2m";
	inline constexpr std::string_view ANSI_ITALIC = "\x1b[3m";
	inline constexpr std::string_view ANSI_UNDERLINE = "\x1b[4m";

	// ==============normal foreground color codes============== //

	inline constexpr std::string_view ANSI_FOREGROUND_BLACK = "\x1b[30m";
	inline constexpr std::string_view ANSI_FOREGROUND_RED = "\x1b[31m";
	inline constexpr std::string_view ANSI_FOREGROUND_GREEN = "\x1b[32m";
	inline constexpr std::string_view ANSI_FOREGROUND_YELLOW = "\x1b[33m";
	inline constexpr std::string_view ANSI_FOREGROUND_BLUE = "\x1b[34m";
	inline constexpr std::string_view ANSI_FOREGROUND_MAGENTA = "\x1b[35m";
	inline constexpr std::string_view ANSI_FOREGROUND_CYAN = "\x1b[36m";
	inline constexpr std::string_view ANSI_FOREGROUND_WHITE = "\x1b[37m";

	// ==============bright foreground color codes============== //

	inline constexpr std::string_view ANSI_FOREGROUND_BRIGHT_BLACK = "\x1b[90m"; // gray
	inline constexpr std::string_view ANSI_FOREGROUND_BRIGHT_RED = "\x1b[91m";
	inline constexpr std::string_view ANSI_FOREGROUND_BRIGHT_GREEN = "\x1b[92m";
	inline constexpr std::string_view ANSI_FOREGROUND_BRIGHT_YELLOW = "\x1b[93m";
	inline constexpr std::string_view ANSI_FOREGROUND_BRIGHT_BLUE = "\x1b[94m";
	inline constexpr std::string_view ANSI_FOREGROUND_BRIGHT_MAGENTA = "\x1b[95m";
	inline constexpr std::string_view ANSI_FOREGROUND_BRIGHT_CYAN = "\x1b[96m";
	inline constexpr std::string_view ANSI_FOREGROUND_BRIGHT_WHITE = "\x1b[97m";

	// ==============normal background color codes============== //

	inline constexpr std::string_view ANSI_BACKGROUND_BLACK = "\x1b[40m";
	inline constexpr std::string_view ANSI_BACKGROUND_RED = "\x1b[41m";
	inline constexpr std::string_view ANSI_BACKGROUND_GREEN = "\x1b[42m";
	inline constexpr std::string_view ANSI_BACKGROUND_YELLOW = "\x1b[43m";
	inline constexpr std::string_view ANSI_BACKGROUND_BLUE = "\x1b[44m";
	inline constexpr std::string_view ANSI_BACKGROUND_MAGENTA = "\x1b[45m";
	inline constexpr std::string_view ANSI_BACKGROUND_CYAN = "\x1b[46m";
	inline constexpr std::string_view ANSI_BACKGROUND_WHITE = "\x1b[47m";

	// ==============bright background color codes============== //

	inline constexpr std::string_view ANSI_BACKGROUND_BRIGHT_BLACK = "\x1b[100m"; // gray
	inline constexpr std::string_view ANSI_BACKGROUND_BRIGHT_RED = "\x1b[101m";
	inline constexpr std::string_view ANSI_BACKGROUND_BRIGHT_GREEN = "\x1b[102m";
	inline constexpr std::string_view ANSI_BACKGROUND_BRIGHT_YELLOW = "\x1b[103m";
	inline constexpr std::string_view ANSI_BACKGROUND_BRIGHT_BLUE = "\x1b[104m";
	inline constexpr std::string_view ANSI_BACKGROUND_BRIGHT_MAGENTA = "\x1b[105m";
	inline constexpr std::string_view ANSI_BACKGROUND_BRIGHT_CYAN = "\x1b[106m";
	inline constexpr std::string_view ANSI_BACKGROUND_BRIGHT_WHITE = "\x1b[107m";

	// ==============alias defines============== //

	inline constexpr std::string_view ALIAS_FOREGROUND_GRAY = ANSI_FOREGROUND_BRIGHT_BLACK;
	inline constexpr std::string_view ALIAS_BACKGROUND_GRAY = ANSI_BACKGROUND_BRIGHT_BLACK;

};
