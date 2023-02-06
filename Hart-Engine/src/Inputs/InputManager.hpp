#pragma once

#include "HartPch.hpp"
#include "Inputs/KeyCodes.hpp"
#include "Inputs/MouseCodes.hpp"
#include "Maths/Vec2.hpp"

namespace Hart {
	namespace Inputs {
		class InputManager {
		public:
			static constexpr int32_t GetMaxKeys();
			static constexpr int32_t GetMaxMouseButtons();
			static bool IsKeyPressed(const KeyCode& keyCode);
			static bool IsKeyReleased(const KeyCode& keyCode);
			static bool IsMouseButtonPressed(const MouseCode& mouseCode);
			static bool IsMouseButtonReleased(const MouseCode& mouseCode);
			static Maths::Vec2 GetMousePosition();
			// sets the cursor's location to the specified location
			static void SetMousePosition(const Maths::Vec2& position);
		private:
			static void Init();
			static void SetKeyPressed(const KeyCode& keyCode);
			static void SetKeyReleased(const KeyCode& keyCode);
			static void SetMouseButtonPressed(const MouseCode& mouseCode);
			static void SetMouseButtonReleased(const MouseCode& mouseCode);
			static void UpdateMousePosition(const Maths::Vec2& mousePosition);
		private:
			static constexpr int32_t MAX_KEYS = 1024;
			static constexpr int32_t MAX_MOUSE_BUTTONS = 512;
			static std::array<bool, MAX_KEYS> s_Keys;
			static std::array<bool, MAX_MOUSE_BUTTONS> s_MouseButtons;
			static Maths::Vec2 s_MousePosition;

			friend class Application;
		};
	}
}