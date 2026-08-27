#pragma once

#include "Maths/Vec2.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/KeyEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/EventDispatcher.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <functional>

namespace Hart {
	struct WindowProps {
	public:
		int32_t width = 640;
		int32_t height = 480;
		int32_t frameBufferWidth = 0;
		int32_t frameBufferHeight = 0;
		std::string title = "Hart Application";
		bool resizable = false;

	private:
		Vec2 position = { 0.0f, 0.0f };
		friend class Window;
	};
	// Class representing the GUI Window
	class Window {
		using EventCallBackFunction = std::function<void(Event&)>;

	public:
		Window(const WindowProps& windowProps);
		~Window();

		void swapBuffers();

		inline int32_t getWidth() const { return m_WindowProps.width; }
		inline int32_t getHeight() const { return m_WindowProps.height; }
		inline int32_t getFrameBufferWidth() const { return m_WindowProps.frameBufferWidth; }
		inline int32_t getFrameBufferHeight() const { return m_WindowProps.frameBufferHeight; }

		inline Vec2 getDimensions() const {
			return Vec2{
				static_cast<float>(m_WindowProps.width),
				static_cast<float>(m_WindowProps.height)
			};
		}
		// returns a non ownning reference to the GLFWwindow object
		inline GLFWwindow* const& getGLFWwindow() const { return m_GLFWwindow; }
		inline const Vec2& getPosition() const { return m_WindowProps.position; }

		friend void windowSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height);
		friend void windowCloseCallback(GLFWwindow* glfwWindow);
		friend void windowPositionCallback(GLFWwindow* glfwWindow, int32_t xpos, int32_t ypos);
		friend void windowFocusCallback(GLFWwindow* glfwWindow, int32_t focused);
		friend void windowIconifyCallback(GLFWwindow* glfwWindow, int iconified);
		friend void windowMaximizedCallback(GLFWwindow* glfwWindow, int maximized);
		friend void framebufferSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height);
		friend void keyCallback(GLFWwindow* glfwWindow, int32_t key, int32_t scancode, int32_t action, int32_t mods);
		friend void mouseButtonCallback(GLFWwindow* glfwWindow, int32_t button, int32_t action, int32_t mods);
		friend void mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset);
		friend void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);

	private:
		void init();
		void deinit();
		inline void setWindowSize(int32_t width, int32_t height) { m_WindowProps.width = width, m_WindowProps.height = height; }
		inline void setWindowPosition(float xpos, float ypos) { m_WindowProps.position.x = xpos, m_WindowProps.position.y = ypos; }
		void registerGLFWcallbacks();
		void setEventCallback(const EventCallBackFunction callbackFn);

	private:
		WindowProps m_WindowProps;
		GLFWwindow* m_GLFWwindow = nullptr;
		EventCallBackFunction m_EventCallbackFn;

		friend class Application;
	};
}
