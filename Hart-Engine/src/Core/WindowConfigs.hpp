/*
* Window configurations class for the application class.
* Stores default values to be used for creating a window, which can be changed as needed.
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	struct WindowConfigs {
	public:
		int32_t winWidth = 640, winHeight = 480;
		std::string title = "Hart Engine: Application";
		Maths::Vec2 position = Maths::Vec2(0.0f, 0.0f);
		bool resiable = false;
	};
}