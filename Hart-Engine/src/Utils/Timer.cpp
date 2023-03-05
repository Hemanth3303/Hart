#include "HartPch.hpp"
#include "Timer.hpp"
#include "Core/HartApplication.hpp"
#include "GLFW/glfw3.h"

namespace Hart {
	namespace Utils {
		double Timer::getTimeInSeconds() {
			HART_ASSERT_NOT_EQUAL(Hart::Application::s_Instance, nullptr);
			HART_ASSERT_NOT_EQUAL(Hart::Application::s_Instance->getWindow(), nullptr);
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