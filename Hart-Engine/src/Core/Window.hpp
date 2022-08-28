#pragma once
#include "HartPch.hpp"

#include "GLFW/glfw3.h"

namespace Hart {
	//manages the glfw window and opengl context
	class Window {
	public:
		Window(int32_t width, int32_t height, const std::string& title);
		Window(const Window&) = delete;
		~Window();

		void init();
		void handleEvents();
		void update();
		void deinit();
	private:
		int32_t m_Width, m_Height;
		std::string m_Title;

		GLFWwindow* m_Window;
	};
}