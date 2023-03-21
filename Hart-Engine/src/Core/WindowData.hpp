#pragma once

#include "HartPch.hpp"
#include "Maths/Vec2.hpp"

namespace Hart {
	// A struct representing Window data with default values
	struct WindowData {
	public:
		WindowData(int32_t width = DEFAULT_WINDOW_WIDTH, int32_t height = DEFAULT_WINDOW_HEIGHT, const std::string& title = "Hart Engine: Application", bool resizable = false)
			:m_Width(width), m_Height(height), m_Title(title), m_Resizable(resizable) {

		}
	public:
		static constexpr int32_t DEFAULT_WINDOW_WIDTH = 640;
		static constexpr int32_t DEFAULT_WINDOW_HEIGHT = 480;
		int32_t m_Width, m_Height;
		std::string m_Title;
		bool m_Resizable;
		Maths::Vec2 m_Position;
	};
}