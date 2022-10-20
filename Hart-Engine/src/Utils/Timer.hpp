/*
* Class to provide timing related functions like fps counter, delta time calculations, etc;
*/

#pragma once

#include "HartPch.hpp"

#include "GLFW/glfw3.h"

namespace Hart {
	namespace Utils {
		class Timer {
		public:
			Timer();
			Timer(const Timer&) = delete;
			~Timer();
			void update();

			//returns the current delta time in seconds
			inline const double& getDeltaTime() const { return m_DeltaTime; }
			inline const double& getFPS() const { return m_FrameRate; }
		private:
			double m_DeltaTime = 0.0;
			double m_Current = 0.0, m_Previous = 0.0;
			double m_FrameRate = 0.0;
		};
	}
}