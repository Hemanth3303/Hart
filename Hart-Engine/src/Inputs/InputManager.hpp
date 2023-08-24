#pragma once

#include "HartPch.hpp"
#include "Inputs/KeyCodes.hpp"
#include "Inputs/MouseCodes.hpp"
#include "Maths/Vec2.hpp"

namespace Hart {
	class Application;
	class InputManager {
	public:
		static constexpr std::int32_t GetMaxKeys();
		static constexpr std::int32_t GetMaxMouseButtons();
		static bool IsKeyPressed(const KeyCode& keyCode);
		static bool IsKeyReleased(const KeyCode& keyCode);
		static bool IsMouseButtonPressed(const MouseCode& mouseCode);
		static bool IsMouseButtonReleased(const MouseCode& mouseCode);
		static const Vec2 GetMousePosition();
		// sets the cursor's location to the specified location
		static void SetMousePosition(const Vec2& position);
		static const KeyCode& GetCurrentKey();
		static const MouseCode& GetCurrentMouseButton();
	private:
		static void Init();
		static void DeInit();

		static void SetKeyPressed(const KeyCode& keyCode);
		static void SetKeyReleased(const KeyCode& keyCode);
		static void SetMouseButtonPressed(const MouseCode& mouseCode);
		static void SetMouseButtonReleased(const MouseCode& mouseCode);
		static void UpdateMousePosition(const Vec2& mousePosition);
		static void SetCurrentKey(const KeyCode& keyCode);
		static void SetCurrentMouseButton(const MouseCode& mouseCode);
	private:
		static constexpr std::int32_t MAX_KEYS = 1024;
		static constexpr std::int32_t MAX_MOUSE_BUTTONS = 512;
		static std::array<bool, MAX_KEYS> s_Keys;
		static std::array<bool, MAX_MOUSE_BUTTONS> s_MouseButtons;
		static Vec2 s_MousePosition;
		static KeyCode s_CurrentKey;
		static MouseCode s_CurrentMouseButton;

		friend class Hart::Application;
	};
}