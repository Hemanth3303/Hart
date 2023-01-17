#include "HartPch.hpp"
#include "InputManager.hpp"
#include "Window.hpp"

namespace Hart {
	namespace Keyboard {
		const bool isKeyDown(Key key) {
			HART_ASSERT_NOT_EQUAL(Window::s_Instance->getGLFWwindow(), nullptr);
			return static_cast<bool>(glfwGetKey(Window::s_Instance->getGLFWwindow(), static_cast<int32_t>(key)) == GLFW_PRESS);
		}
		const bool isKeyUp(Key key) {
			return !isKeyDown(key);
		}
	}

	namespace Mouse {
		const bool isButtonDown(Button button) {
			HART_ASSERT_NOT_EQUAL(Window::s_Instance->getGLFWwindow(), nullptr);
			return static_cast<bool>(glfwGetMouseButton(Window::s_Instance->getGLFWwindow(), static_cast<int32_t>(button)) == GLFW_PRESS);
		}
		const bool isButtonUp(Button button) {
			return !isButtonDown(button);
		}
	}

	namespace JoyStick {
		//TODO: Implement
	}

	namespace GamePad {
		//TODO: Implement
	}
}