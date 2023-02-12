#include "HartPch.hpp"
#include "InputManager.hpp"
#include "Core/HartApplication.hpp"
#include "GLFW/glfw3.h"

namespace Hart {
	namespace Inputs {
		std::array<bool, InputManager::MAX_KEYS> InputManager::s_Keys;
		std::array<bool, InputManager::MAX_MOUSE_BUTTONS> InputManager::s_MouseButtons;
		Maths::Vec2 InputManager::s_MousePosition;
		KeyCode InputManager::s_CurrentKey=KeyCode::Unknown;
		MouseCode InputManager::s_CurrentMouseButton=MouseCode::Unknown;

		constexpr int32_t InputManager::GetMaxKeys() {
			return MAX_KEYS;
		}

		constexpr int32_t InputManager::GetMaxMouseButtons() {
			return MAX_MOUSE_BUTTONS;
		}

		bool InputManager::IsKeyPressed(const KeyCode& keyCode) {
			return s_Keys[static_cast<int32_t>(keyCode)];
		}

		bool InputManager::IsKeyReleased(const KeyCode& keyCode) {
			return !IsKeyPressed(keyCode);
		}

		bool InputManager::IsMouseButtonPressed(const MouseCode& mouseCode) {
			return s_MouseButtons[static_cast<int32_t>(mouseCode)];
		}

		bool InputManager::IsMouseButtonReleased(const MouseCode& mouseCode) {
			return !IsMouseButtonPressed(mouseCode);
		}

		const Maths::Vec2 InputManager::GetMousePosition() {
			return s_MousePosition;
		}

		void InputManager::SetMousePosition(const Maths::Vec2& position) {
			HART_ASSERT_NOT_EQUAL(Hart::Application::s_Instance, nullptr);
			glfwSetCursorPos(Hart::Application::s_Instance->getWindow()->getGLFWwindow(), position.x, position.y);
		}

		const KeyCode& InputManager::GetCurrentKey() {
			return s_CurrentKey;
		}

		const MouseCode& InputManager::GetCurrentMouseButton() {
			return s_CurrentMouseButton;
		}

		void InputManager::Init() {
			for (bool& key : s_Keys) {
				key = false;
			}
			for (bool& mouseButton : s_MouseButtons) {
				mouseButton = false;
			}
			s_MousePosition = Maths::Vec2(0.0f, 0.0f);
		}

		void InputManager::SetKeyPressed(const KeyCode& keyCode) {
			s_Keys[static_cast<int32_t>(keyCode)] = true;
			SetCurrentKey(keyCode);
		}

		void InputManager::SetKeyReleased(const KeyCode& keyCode) {
			s_Keys[static_cast<int32_t>(keyCode)] = false;
			SetCurrentKey(KeyCode::Unknown);
		}

		void InputManager::SetMouseButtonPressed(const MouseCode& mouseCode) {
			s_MouseButtons[static_cast<int32_t>(mouseCode)] = true;
			SetCurrentMouseButton(mouseCode);
		}

		void InputManager::SetMouseButtonReleased(const MouseCode& mouseCode) {
			s_MouseButtons[static_cast<int32_t>(mouseCode)] = false;
			SetCurrentMouseButton(MouseCode::Unknown);
		}

		void InputManager::UpdateMousePosition(const Maths::Vec2& mousePosition) {
			s_MousePosition = mousePosition;
		}

		void InputManager::SetCurrentKey(const KeyCode& keyCode) {
			s_CurrentKey = keyCode;
		}

		void InputManager::SetCurrentMouseButton(const MouseCode& mouseCode) {
			s_CurrentMouseButton = mouseCode;
		}
	}
}