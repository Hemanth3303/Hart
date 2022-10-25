#pragma once
#include "HartPch.hpp"
#include "Input.hpp"
#include "Maths/Maths.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hart {
	//manages the glfw window and opengl context
	class Window {
	public:
		Window(int32_t width, int32_t height, const std::string& title, const bool& resizable);
		Window(const Window&) = delete;
		~Window();

		void handleEvents();
		void update();
		void clear();
		void swapBuffers();
		void enableVsync();
		void disableVsync();

		inline GLFWwindow*& getGlfwWindow() { return m_Window; }
		inline const int32_t getWidth() const { return m_Width; }
		inline const int32_t getHeight() const { return m_Height; }
		inline const Maths::Vec2& getMousePosition() const { return m_MousePosition; }

	private:
		void init();
		void deinit();

		friend void frameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
		friend void cursonPositionCallback(GLFWwindow* window, double xpos, double ypos);
	public:
		static Window* INSTANCE;
	private:
		int32_t m_Width, m_Height;
		std::string m_Title;
		bool m_Resizable;
		Maths::Vec2 m_MousePosition = Maths::Vec2();

		GLFWwindow* m_Window;
	};
	
	void frameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
	void cursonPositionCallback(GLFWwindow* window, double xpos, double ypos);
}