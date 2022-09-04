#pragma once

#include "HartPch.hpp"
#include "Window.hpp"

#include "GLFW/glfw3.h"

namespace Hart {
	//Main class that initializes all other engine subsystems
	class Application {
	public:
		//Specify width, height, name of the window and optionall, if the window is resizable or not(default is false)
		Application(int32_t width, int32_t height, const std::string& title, bool resizable = false);
		virtual ~Application();

		void handleEvents();
		void update();
		void render();

		inline const bool& isRunning() const { return m_IsRunning; }
		inline const Window& getWindow() const { return m_Window; }
	private:
		void init();
		void deinit();
	private:
		Window m_Window;
		bool m_IsRunning;
	};
}