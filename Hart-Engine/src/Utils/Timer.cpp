#include "HartPch.hpp"
#include "Timer.hpp"

namespace Hart {
	namespace Utils {
		std::chrono::high_resolution_clock::time_point Timer::m_TimePoint;

		void Timer::Init() {
			HART_ENGINE_LOG("Initialized Timer");
			m_TimePoint = std::chrono::high_resolution_clock::now();
		}

		double Timer::getTimeInSeconds() {
			std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = timePoint2 - m_TimePoint;
			return std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();

		}

		double Timer::getTimeInMilliSeconds() {
			std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = timePoint2 - m_TimePoint;
			return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
		}

		double Timer::getTimeInMicroSeconds() {
			std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = timePoint2 - m_TimePoint;
			return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		}

		double Timer::getTimeInNanoSeconds() {
			std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = timePoint2 - m_TimePoint;
			return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
		}

		void Timer::DeInit() {
			HART_ENGINE_LOG("DeInitialized Timer");
		}

	}
}