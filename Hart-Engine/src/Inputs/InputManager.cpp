#include "HartPch.hpp"
#include "InputManager.hpp"
#include "Core/HartApplication.hpp"
#include "GLFW/glfw3.h"

namespace Hart {
	std::array<bool, InputManager::MAX_KEYS> InputManager::s_Keys;
	std::array<bool, InputManager::MAX_MOUSE_BUTTONS> InputManager::s_MouseButtons;
	Vec2 InputManager::s_MousePosition;
	KeyCode InputManager::s_CurrentKey = KeyCode::Unknown;
	MouseCode InputManager::s_CurrentMouseButton = MouseCode::Unknown;

	constexpr std::int32_t InputManager::GetMaxKeys() {
		return MAX_KEYS;
	}

	constexpr std::int32_t InputManager::GetMaxMouseButtons() {
		return MAX_MOUSE_BUTTONS;
	}

	bool InputManager::IsKeyPressed(const KeyCode& keyCode) {
		if (keyCode == KeyCode::Unknown) {
			return false;
		}
		return s_Keys[static_cast<std::int32_t>(keyCode)];
	}

	bool InputManager::IsKeyReleased(const KeyCode& keyCode) {
		if (keyCode == KeyCode::Unknown) {
			return false;
		}
		return !IsKeyPressed(keyCode);
	}

	bool InputManager::IsMouseButtonPressed(const MouseCode& mouseCode) {
		if (mouseCode == MouseCode::Unknown) {
			return false;
		}
		return s_MouseButtons[static_cast<std::int32_t>(mouseCode)];
	}

	bool InputManager::IsMouseButtonReleased(const MouseCode& mouseCode) {
		if (mouseCode == MouseCode::Unknown) {
			return false;
		}
		return !IsMouseButtonPressed(mouseCode);
	}

	const Vec2 InputManager::GetMousePosition() {
		return s_MousePosition;
	}

	void InputManager::SetMousePosition(const Vec2& position) {
		HART_ASSERT_NOT_EQUAL(Hart::Application::Get(), nullptr);
		glfwSetCursorPos(Hart::Application::Get()->getWindow()->getGLFWwindow(), position.x, position.y);
	}

	const KeyCode& InputManager::GetCurrentKey() {
		return s_CurrentKey;
	}

	const MouseCode& InputManager::GetCurrentMouseButton() {
		return s_CurrentMouseButton;
	}

	void InputManager::Init() {
		HART_ENGINE_LOG("Initializing Input Manager");
		for (bool& key : s_Keys) {
			key = false;
		}
		for (bool& mouseButton : s_MouseButtons) {
			mouseButton = false;
		}
		s_MousePosition = Vec2(0.0f, 0.0f);
	}

	void InputManager::DeInit() {
		HART_ENGINE_LOG("DeInitializing Input Manager");
	}

	void InputManager::SetKeyPressed(const KeyCode& keyCode) {
		s_Keys[static_cast<std::int32_t>(keyCode)] = true;
		SetCurrentKey(keyCode);
	}

	void InputManager::SetKeyReleased(const KeyCode& keyCode) {
		s_Keys[static_cast<std::int32_t>(keyCode)] = false;
		SetCurrentKey(KeyCode::Unknown);
	}

	void InputManager::SetMouseButtonPressed(const MouseCode& mouseCode) {
		s_MouseButtons[static_cast<std::int32_t>(mouseCode)] = true;
		SetCurrentMouseButton(mouseCode);
	}

	void InputManager::SetMouseButtonReleased(const MouseCode& mouseCode) {
		s_MouseButtons[static_cast<std::int32_t>(mouseCode)] = false;
		SetCurrentMouseButton(MouseCode::Unknown);
	}

	void InputManager::UpdateMousePosition(const Vec2& mousePosition) {
		s_MousePosition = mousePosition;
	}

	void InputManager::SetCurrentKey(const KeyCode& keyCode) {
		s_CurrentKey = keyCode;
	}

	void InputManager::SetCurrentMouseButton(const MouseCode& mouseCode) {
		s_CurrentMouseButton = mouseCode;
	}
}