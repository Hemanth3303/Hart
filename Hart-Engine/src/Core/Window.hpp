/*
* Class representing the gui window
*/

#pragma once

#include "HartPch.hpp"
#include "Maths/Vec2.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Maths/Vec2.hpp"

namespace Hart {
	class Window {
	public:
		Window(int32_t width, int32_t height, const std::string& title, bool resizable = false);
		~Window();

		void init();

		inline const int32_t& getWidth() const { return m_Width; }
		inline const int32_t& getHeight() const { return m_Height; }
		inline GLFWwindow*& getGLFWwindow() { return m_Window; }
		inline const Maths::Vec2& getMousePosition() const { return m_MousePos; }
		
		void setMousePosition(const Maths::Vec2& position) const;

		friend void framebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
		friend void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
	public:
		static Window* s_Instance;
	private:
		int32_t m_Width, m_Height;
		std::string m_Title;
		bool m_Resizable;
		GLFWwindow* m_Window = nullptr;
		Maths::Vec2 m_MousePos;
	};
	void framebufferSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height);
	void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
}