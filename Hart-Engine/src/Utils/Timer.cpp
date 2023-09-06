#include "HartPch.hpp"
#include "Timer.hpp"

namespace Hart {
	std::chrono::high_resolution_clock::time_point Timer::s_TimePoint;
	bool Timer::s_IsInitialized = false;
	std::string Timer::s_CurrentTimeStamp = std::string("TTT");

	void Timer::Init() {
		HART_ASSERT_NOT_EQUAL(s_IsInitialized, true, "Reason: Timer already initialized once. Do not initialize timer more than once");
		s_TimePoint = std::chrono::high_resolution_clock::now();
		s_IsInitialized = true;
		HART_ENGINE_LOG("Initializing Timer");
	}

	void Timer::DeInit() {
		HART_ENGINE_LOG("DeInitializing Timer");
	}

	double Timer::GetTimeInSeconds() {
		HART_ASSERT_EQUAL(s_IsInitialized, true, "Reason: Timer not Initialized");
		std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTime = timePoint2 - s_TimePoint;
		return static_cast<double>(std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count());

	}

	double Timer::GetTimeInMilliSeconds() {
		std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTime = timePoint2 - s_TimePoint;
		return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count());
	}

	double Timer::GetTimeInMicroSeconds() {
		std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTime = timePoint2 - s_TimePoint;
		return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count());
	}

	double Timer::GetTimeInNanoSeconds() {
		std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTime = timePoint2 - s_TimePoint;
		return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedTime).count());
	}

	std::string_view Timer::GetCurrentTimeStamp() {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
		s_CurrentTimeStamp = ss.str();

		return s_CurrentTimeStamp;
	}
}