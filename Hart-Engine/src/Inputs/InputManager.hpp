#pragma once

#include "HartPch.hpp"
#include "Inputs/KeyCodes.hpp"
#include "Inputs/MouseCodes.hpp"
#include "Maths/Vec2.hpp"

namespace Hart {
	class Application;
	namespace Inputs {
		class InputManager {
		public:
			static constexpr int32_t GetMaxKeys();
			static constexpr int32_t GetMaxMouseButtons();
			static bool IsKeyPressed(const KeyCode& keyCode);
			static bool IsKeyReleased(const KeyCode& keyCode);
			static bool IsMouseButtonPressed(const MouseCode& mouseCode);
			static bool IsMouseButtonReleased(const MouseCode& mouseCode);
			static const Maths::Vec2 GetMousePosition();
			// sets the cursor's location to the specified location
			static void SetMousePosition(const Maths::Vec2& position);
			static const KeyCode& GetCurrentKey();
			static const MouseCode& GetCurrentMouseButton();
		private:
			static void Init();
			static void SetKeyPressed(const KeyCode& keyCode);
			static void SetKeyReleased(const KeyCode& keyCode);
			static void SetMouseButtonPressed(const MouseCode& mouseCode);
			static void SetMouseButtonReleased(const MouseCode& mouseCode);
			static void UpdateMousePosition(const Maths::Vec2& mousePosition);
			static void SetCurrentKey(const KeyCode& keyCode);
			static void SetCurrentMouseButton(const MouseCode& mouseCode);
		private:
			static constexpr int32_t MAX_KEYS = 1024;
			static constexpr int32_t MAX_MOUSE_BUTTONS = 512;
			static std::array<bool, MAX_KEYS> s_Keys;
			static std::array<bool, MAX_MOUSE_BUTTONS> s_MouseButtons;
			static Maths::Vec2 s_MousePosition;
			static KeyCode s_CurrentKey;
			static MouseCode s_CurrentMouseButton;

			friend class Hart::Application;
		};
	}
}