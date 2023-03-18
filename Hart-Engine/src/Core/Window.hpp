/*
* Class representing the gui window
*/

#pragma once

#include "HartPch.hpp"
#include "WindowData.hpp"
#include "Maths/Vec2.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/KeyEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/EventDispatcher.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hart {
	class Window {
		using EventCallBackFunction = std::function<void(Events::Event&)>;
	public:
		Window(const WindowData& windowData);
		~Window();

		void swapBuffers();

		inline const int32_t& getWidth() const { return m_WindowData.m_Width; }
		inline const int32_t& getHeight() const { return m_WindowData.m_Height; }
		// returns a non ownning reference to the GLFWwindow object
		inline GLFWwindow* const& getGLFWwindow() const { return m_GLFWwindow; }
		inline const Maths::Vec2& getPosition() const { return m_WindowData.m_Position; }

		friend void windowSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height);
		friend void windowCloseCallback(GLFWwindow* glfwWindow);
		friend void windowPositionCallback(GLFWwindow* glfwWindow, int32_t xpos, int32_t ypos);
		friend void windowFocusCallback(GLFWwindow* glfwWindow, int32_t focused);
		friend void framebufferSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height);
		friend void keyCallback(GLFWwindow* glfwWindow, int32_t key, int32_t scancode, int32_t action, int32_t mods);
		friend void mouseButtonCallback(GLFWwindow* glfwWindow, int32_t button, int32_t action, int32_t mods);
		friend void mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset);
		friend void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
	private:
		void init();
		inline void setWindowSize(int32_t width, int32_t height) { m_WindowData.m_Width = width, m_WindowData.m_Height = height; }
		inline void setWindowPosition(float xpos, float ypos) { m_WindowData.m_Position.x = xpos, m_WindowData.m_Position.y = ypos; }
		void setEventCallback(const EventCallBackFunction callbackFn);
	private:
		WindowData m_WindowData;
		GLFWwindow* m_GLFWwindow = nullptr;
		EventCallBackFunction m_EventCallbackFn;

		friend class Application;
	};

	void windowSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height);
	void windowCloseCallback(GLFWwindow* glfwWindow);
	void windowPositionCallback(GLFWwindow* glfwWindow, int32_t xpos, int32_t ypos);
	void windowFocusCallback(GLFWwindow* glfwWindow, int32_t focused);
	void framebufferSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height);
	void keyCallback(GLFWwindow* glfwWindow, int32_t key, int32_t scancode, int32_t action, int32_t mods);
	void mouseButtonCallback(GLFWwindow* glfwWindow, int32_t button, int32_t action, int32_t mods);
	void mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset);
	void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
}