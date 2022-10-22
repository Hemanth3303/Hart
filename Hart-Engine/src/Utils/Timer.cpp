#include "HartPch.hpp"
#include "Timer.hpp"

namespace Hart {
	namespace Utils {
		Timer::Timer() {

			m_Current = glfwGetTime();

			update();
		}

		Timer::~Timer() {

		}

		void Timer::update() {
			m_Current = glfwGetTime();
			m_DeltaTime = m_Current - m_Previous;
			m_FrameRate = 1 / m_DeltaTime;
			m_Previous = m_Current;
		}
	}
}