#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace Hart {
	class Timer {
	public:
		static uint64_t GetTimepointNanoseconds();
		static uint64_t GetTimepointMicroseconds();
		static uint64_t GetTimepointMilliseconds();
		static uint64_t GetTimepointSeconds();

		static std::string GetTimeStampUTC();
		static std::string GetTimeStampLocalTime();
	};
}
