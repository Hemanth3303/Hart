#include "HartPch.hpp"
#include "Input.hpp"
#include "Window.hpp"

#include "GLFW/glfw3.h"

namespace Hart {

	namespace KeyBoard {
		bool isKeyPressed(Key key) {
			HART_ASSERT_NOT_EQUALS(Window::INSTANCE, nullptr);
			return (glfwGetKey(Window::INSTANCE->getGlfwWindow(), static_cast<int>(key)) == GLFW_PRESS);
		}
		bool isKeyReleased(Key key) {
			HART_ASSERT_NOT_EQUALS(Window::INSTANCE, nullptr);
			return !(isKeyPressed(key));
		}
	}

	namespace Mouse {
		bool isButtonPressed(Button button) {
			HART_ASSERT_NOT_EQUALS(Window::INSTANCE, nullptr);
			return (glfwGetMouseButton(Window::INSTANCE->getGlfwWindow(), static_cast<int>(button)) == GLFW_PRESS);
		}
		bool isButtonReleased(Button button) {
			HART_ASSERT_NOT_EQUALS(Window::INSTANCE, nullptr);
			return !isButtonPressed(button);
		}
		const Maths::Vec2& getMousePosition() {
			HART_ASSERT_NOT_EQUALS(Window::INSTANCE, nullptr);
			return Window::INSTANCE->getMousePosition();
		}
	}

	//TODO: Implement these
	namespace JoyStick {
		//doesn't work
		bool isButtonPressed(Button button) {
			HART_ASSERT_NOT_EQUALS(Window::INSTANCE, nullptr);
			return false;
		}
		//doesn't work
		bool isButtonReleased(Button button) {
			HART_ASSERT_NOT_EQUALS(Window::INSTANCE, nullptr);
			return false;
		}
	}
}