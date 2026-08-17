#pragma once

#include <cstdint>
#include <string>

namespace Hart {
	class Timer {
	public:
		// uses the monotonic std::chrono::steady_clock
		static uint64_t GetTimepointNanoseconds();
		// uses the monotonic std::chrono::steady_clock
		static uint64_t GetTimepointMicroseconds();
		// uses the monotonic std::chrono::steady_clock
		static uint64_t GetTimepointMilliseconds();
		// uses the monotonic std::chrono::steady_clock
		static uint64_t GetTimepointSeconds();

		// uses the realtime std::chrono::system_clock
		static std::string GetTimeStampUTC();
		// uses the realtime std::chrono::system_clock
		static std::string GetTimeStampLocalTime();
	};
}
