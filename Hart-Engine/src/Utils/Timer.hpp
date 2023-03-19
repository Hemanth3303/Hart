/*
* Class for timing functions
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		class Timer {
		public:
			static void Init();
			// time since window creation
			static double getTimeInSeconds();
			static double getTimeInMilliSeconds();
			static double getTimeInMicroSeconds();
			static double getTimeInNanoSeconds();
			static void DeInit();
		private:
			static std::chrono::high_resolution_clock::time_point m_TimePoint;
		};
	}
}