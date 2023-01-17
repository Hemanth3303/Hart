#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		class Timer {
		public:
			// time since window creation
			static double getTimeInSeconds();
			static double getTimeInMilliSeconds();
			static double getTimeInMicroSeconds();
			static double getTimeInNanoSeconds();
		};
	}
}