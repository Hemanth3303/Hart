#include "HartPch.hpp"
#include "Timer.hpp"

#include <chrono>
#include <iomanip>
#include <ctime>

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
		auto now = std::chrono::system_clock::now();
		auto seconds = std::chrono::floor<std::chrono::seconds>(
			now.time_since_epoch());
		auto nanoseconds = std::chrono::floor<std::chrono::nanoseconds>(
							   now.time_since_epoch() - seconds)
							   .count();

		const std::time_t epochSeconds = std::chrono::system_clock::to_time_t(now);
		std::tm calendarTime{};

#if defined(HART_ENGINE_PLATFORM_WINDOWS)
		gmtime_s(&calendarTime, &epochSeconds);
#else
		gmtime_r(&epochSeconds, &calendarTime);
#endif

		std::ostringstream oss;

		oss
			<< std::put_time(&calendarTime, "%Y-%m-%dT%H:%M:%S")
			<< '.'
			<< std::setfill('0') << std::setw(Timer::NANOSECOND_STRING_LENGTH) << nanoseconds
			<< 'Z';

		return oss.str();
	}

	// yes i know both are 95% similar, leave me alone
	// can't think of a way to cleanly abstract the common parts out
	// since both needs the initial nanoseconds too
	std::string Timer::GetTimeStampLocalTime() {
		auto now = std::chrono::system_clock::now();
		auto seconds = std::chrono::floor<std::chrono::seconds>(
			now.time_since_epoch());
		auto nanoseconds = std::chrono::floor<std::chrono::nanoseconds>(
							   now.time_since_epoch() - seconds)
							   .count();

		const std::time_t epochSeconds = std::chrono::system_clock::to_time_t(now);
		std::tm calendarTime{};

#if defined(HART_ENGINE_PLATFORM_WINDOWS)
		localtime_s(&calendarTime, &epochSeconds);
#else
		localtime_r(&epochSeconds, &calendarTime);
#endif

		std::ostringstream oss;

		oss
			<< std::put_time(&calendarTime, "%Y-%m-%dT%H:%M:%S")
			<< '.'
			<< std::setfill('0') << std::setw(Timer::NANOSECOND_STRING_LENGTH) << nanoseconds;

		return oss.str();
	}
}
