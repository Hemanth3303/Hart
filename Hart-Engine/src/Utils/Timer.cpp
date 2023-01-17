#include "HartPch.hpp"
#include "Timer.hpp"
#include "Core/Window.hpp"
#include "GLFW/glfw3.h"

namespace Hart {
	namespace Utils {
		double Timer::getTimeInSeconds() {
			HART_ASSERT_NOT_EQUAL(Hart::Window::s_Instance, nullptr);
			return glfwGetTime();
		}

		double Timer::getTimeInMilliSeconds() {
			return getTimeInSeconds() * 1000;
		}

		double Timer::getTimeInMicroSeconds() {
			return getTimeInSeconds() * 1000000;
		}

		double Timer::getTimeInNanoSeconds() {
			return getTimeInSeconds() * 1000000000;
		}

	}
}