#pragma once
#include "HartPch.hpp"
#include "Input.hpp"

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

		inline GLFWwindow*& getGlfwWindow() { return m_Window; }
		inline const int32_t getWidth() const { return m_Width; }
		inline const int32_t getHeight() const { return m_Height; }

	private:
		void init();
		void deinit();

		friend void frameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
	private:
		int32_t m_Width, m_Height;
		std::string m_Title;
		bool m_Resizable;

		GLFWwindow* m_Window;
	public:
		static Window* INSTANCE;
	};
	
	void frameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
}