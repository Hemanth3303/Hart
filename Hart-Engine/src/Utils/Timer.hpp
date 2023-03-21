/*
* Class for timing functions
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	class Application;
	namespace Utils {
		class Timer {
		public:
			static double getTimeInSeconds();
			static double getTimeInMilliSeconds();
			static double getTimeInMicroSeconds();
			static double getTimeInNanoSeconds();
		private:
			// Should be initialized only once during lifetime of Hart::Application
			static void Init();
			static void DeInit();
		private:
			static std::chrono::high_resolution_clock::time_point s_TimePoint;
			static bool s_IsInitialized;
			
			friend class Hart::Application;
		};
	}
}