#include "HartPch.hpp"
#include "Window.hpp"
#include "Graphics/Renderer/RenderCommand.hpp"

namespace Hart {
	
	void windowSizeCallback(GLFWwindow* glfwWindow, std::int32_t width, std::int32_t height);
	void windowCloseCallback(GLFWwindow* glfwWindow);
	void windowPositionCallback(GLFWwindow* glfwWindow, std::int32_t xpos, std::int32_t ypos);
	void windowFocusCallback(GLFWwindow* glfwWindow, std::int32_t focused);
	void framebufferSizeCallback(GLFWwindow* glfwWindow, std::int32_t width, std::int32_t height);
	void keyCallback(GLFWwindow* glfwWindow, std::int32_t key, std::int32_t scancode, std::int32_t action, std::int32_t mods);
	void mouseButtonCallback(GLFWwindow* glfwWindow, std::int32_t button, std::int32_t action, std::int32_t mods);
	void mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset);
	void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);

	Window::Window(const WindowProps& windowProps)
		: m_WindowProps(windowProps) {
		init();
	}

	Window::~Window() {
		deinit();
		HART_ENGINE_LOG("DeInitializing Window");
	}

    void Window::swapBuffers() {
		glfwSwapBuffers(m_GLFWwindow);
    }

	void Window::init() {
		glfwWindowHint(GLFW_RESIZABLE, m_WindowProps.resizable);
		HART_ENGINE_LOG("Initializing Window");
		m_GLFWwindow = glfwCreateWindow(m_WindowProps.width, m_WindowProps.height, m_WindowProps.title.c_str(), nullptr, nullptr);
		HART_ASSERT_NOT_EQUAL(m_GLFWwindow, nullptr, "Reason: Failed to create GLFWwindow");
		HART_ENGINE_LOG("Window initialized successfully");
		glfwMakeContextCurrent(m_GLFWwindow);
		glfwSetWindowUserPointer(m_GLFWwindow, static_cast<void*>(this));

		glfwSetWindowSizeCallback(m_GLFWwindow, windowSizeCallback);
		glfwSetWindowCloseCallback(m_GLFWwindow, windowCloseCallback);
		glfwSetWindowPosCallback(m_GLFWwindow, windowPositionCallback);
		glfwSetWindowFocusCallback(m_GLFWwindow, windowFocusCallback);

		glfwSetFramebufferSizeCallback(m_GLFWwindow, framebufferSizeCallback);

		glfwSetKeyCallback(m_GLFWwindow, keyCallback);

		glfwSetCursorPosCallback(m_GLFWwindow, cursorPositionCallback);
		glfwSetScrollCallback(m_GLFWwindow, mouseScrollCallback);
		glfwSetMouseButtonCallback(m_GLFWwindow, mouseButtonCallback);

		std::int32_t success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HART_ASSERT_NOT_EQUAL(success, -1, "Failed to Initialize GLAD");
		HART_ENGINE_LOG("GLAD loaded successfully");

		RenderCommand::SetViewPort(0, 0, m_WindowProps.width, m_WindowProps.height);

		std::int32_t x, y;
		glfwGetWindowPos(m_GLFWwindow, &x, &y);
		m_WindowProps.position.x = static_cast<float>(x);
		m_WindowProps.position.y = static_cast<float>(y);
	}

	void Window::deinit() {
		glfwDestroyWindow(m_GLFWwindow);
	}

	void Window::setEventCallback(const EventCallBackFunction callbackFn) {
		m_EventCallbackFn = callbackFn;
	}

	void windowSizeCallback(GLFWwindow* glfwWindow, std::int32_t width, std::int32_t height) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		engineWindow->m_WindowProps.width = width;
		engineWindow->m_WindowProps.height = height;

		WindowResizedEvent e(width, height);
		engineWindow->m_EventCallbackFn(e);
	}

	void windowCloseCallback(GLFWwindow* glfwWindow) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		WindowClosedEvent e;
		engineWindow->m_EventCallbackFn(e);
	}

	void windowPositionCallback(GLFWwindow* glfwWindow, std::int32_t xpos, std::int32_t ypos) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		WindowMovedEvent e(static_cast<float>(xpos), static_cast<float>(ypos));
		engineWindow->m_EventCallbackFn(e);
	}

	void windowFocusCallback(GLFWwindow* glfwWindow, std::int32_t focused) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		if (focused == GLFW_TRUE) {
			WindowFocusGainedEvent e;
			engineWindow->m_EventCallbackFn(e);
		}
		else {
			WindowFocusLostEvent e;
			engineWindow->m_EventCallbackFn(e);
		}
	}

	void framebufferSizeCallback(GLFWwindow* glfwWindow, std::int32_t width, std::int32_t height) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		engineWindow->m_WindowProps.width = width;
		engineWindow->m_WindowProps.height = height;

		RenderCommand::SetViewPort(0, 0, engineWindow->m_WindowProps.width, engineWindow->m_WindowProps.height);
	}

	void keyCallback(GLFWwindow* glfwWindow, std::int32_t key, std::int32_t scancode, std::int32_t action, std::int32_t mods) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		static std::int32_t previousKey = -1, repeatCount = 0;

		switch (action) {
			case GLFW_PRESS: {
				repeatCount = 0;
				previousKey = key;
				KeyPressedEvent e(static_cast<KeyCode>(key));
				engineWindow->m_EventCallbackFn(e);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent e(static_cast<KeyCode>(key));
				engineWindow->m_EventCallbackFn(e);
				break;
			}
			case GLFW_REPEAT: {
				if (key == previousKey) {
					repeatCount++;
				}
				else {
					repeatCount = 0;
				}
				previousKey = key;
				KeyRepeatEvent e(static_cast<KeyCode>(key), repeatCount);
				engineWindow->m_EventCallbackFn(e);
				break;
			}
		}

	}

	void mouseButtonCallback(GLFWwindow* glfwWindow, std::int32_t button, std::int32_t action, std::int32_t mods) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		
		switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent e(static_cast<MouseCode>(button));
				engineWindow->m_EventCallbackFn(e);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent e(static_cast<MouseCode>(button));
				engineWindow->m_EventCallbackFn(e);
				break;
			}
		}
	}

	void mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		MouseWheelScrolledEvent e(static_cast<float>(xoffset), static_cast<float>(yoffset));
		engineWindow->m_EventCallbackFn(e);
	}

	void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		MouseMovedEvent e(static_cast<float>(xpos), static_cast<float>(ypos));
		engineWindow->m_EventCallbackFn(e);
	}
}