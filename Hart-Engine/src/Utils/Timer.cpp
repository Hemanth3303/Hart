#include "HartPch.hpp"
#include "Timer.hpp"

namespace Hart {
	namespace Utils {
		std::chrono::high_resolution_clock::time_point Timer::s_TimePoint;
		bool Timer::s_IsInitialized = false;

		void Timer::Init() {
			if (s_IsInitialized) {
				HART_ENGINE_FATAL("Timer already initialized once. Do not initialize timer more than once");
				HART_ASSERT_NOT_EQUAL(s_IsInitialized, true);
				return;
			}
			s_TimePoint = std::chrono::high_resolution_clock::now();
			s_IsInitialized = true;
			HART_ENGINE_LOG("Initialized Timer");
		}

		double Timer::getTimeInSeconds() {
			std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsedTime = timePoint2 - s_TimePoint;
			return static_cast<double>(std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count());

		}

		double Timer::getTimeInMilliSeconds() {
			std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsedTime = timePoint2 - s_TimePoint;
			return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count());
		}

		double Timer::getTimeInMicroSeconds() {
			std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsedTime = timePoint2 - s_TimePoint;
			return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count());
		}

		double Timer::getTimeInNanoSeconds() {
			std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsedTime = timePoint2 - s_TimePoint;
			return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedTime).count());
		}

		void Timer::DeInit() {
			HART_ENGINE_LOG("DeInitialized Timer");
		}

	}
}