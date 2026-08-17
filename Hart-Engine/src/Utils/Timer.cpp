#include "HartPch.hpp"
#include "Timer.hpp"

#include <chrono>

namespace Hart {
	uint64_t Timer::GetTimepointNanoseconds() {
		auto timepoint = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
							timepoint.time_since_epoch())
							.count();

		return static_cast<uint64_t>(duration);
	}

	uint64_t Timer::GetTimepointMicroseconds() {
		return (GetTimepointNanoseconds() / 1'000);
	}

	uint64_t Timer::GetTimepointMilliseconds() {
		return (GetTimepointNanoseconds() / 1'000'000);
	}

	uint64_t Timer::GetTimepointSeconds() {
		return (GetTimepointNanoseconds() / 1'000'000'000);
	}

	std::string Timer::GetTimeStampUTC() {
		return std::string();
	}

	std::string Timer::GetTimeStampLocalTime() {
		return std::string();
	}
}
