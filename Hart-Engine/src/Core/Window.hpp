/*
* Class representing the gui window
*/

#pragma once

#include "HartPch.hpp"
#include "Maths/Vec2.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hart {
	class Window {
	public:
		Window(int32_t width, int32_t height, const std::string& title, bool resizable = false);
		~Window();

		void init();

		inline const int32_t& getWidth() const { return m_Width; }
		inline const int32_t& getHeight() const { return m_Height; }
		inline GLFWwindow*& getGLFWwindow() { return m_Window; }

		friend void framebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
	private:
		int32_t m_Width, m_Height;
		std::string m_Title;
		bool m_Resizable;
		GLFWwindow* m_Window = nullptr;
	};
	void framebufferSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height);
}