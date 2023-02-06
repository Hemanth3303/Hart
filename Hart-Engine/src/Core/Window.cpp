#include "HartPch.hpp"
#include "Window.hpp"

namespace Hart {
	Window::Window(int32_t width, int32_t height, const std::string& title, bool resizable)
		:m_Width(width), m_Height(height), m_Title(title), m_Resizable(resizable) {
		init();

		HART_ASSERT_NOT_EQUAL(m_Window, nullptr);
	}

	Window::~Window() {
		HART_ENGINE_LOG("Closing GLFW");
		glfwTerminate();
		HART_ENGINE_LOG("Closing Window");
	}

	void Window::init() {
		glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
		HART_ENGINE_LOG("Initializing Window");
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		HART_ASSERT_NOT_EQUAL(m_Window, nullptr);
		HART_ENGINE_LOG("Window initialized successfully");
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, static_cast<void*>(this));

		glfwSetWindowSizeCallback(m_Window, windowSizeCallback);
		glfwSetWindowCloseCallback(m_Window, windowCloseCallback);
		glfwSetWindowPosCallback(m_Window, windowPositionCallback);
		glfwSetWindowFocusCallback(m_Window, windowFocusCallback);

		glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);

		glfwSetKeyCallback(m_Window, keyCallback);
		
		glfwSetCursorPosCallback(m_Window, cursorPositionCallback);
		glfwSetScrollCallback(m_Window, mouseScrollCallback);
		glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);

		int32_t success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HART_ASSERT_NOT_EQUAL(success, -1);
		HART_ENGINE_LOG("GLAD loaded successfully");

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, m_Width, m_Height);
	}

	void Window::setEventCallback(const EventCallBackFunction callbackFn) {
		m_EventCallbackFn = callbackFn;
	}

	void windowSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		engineWindow->m_Width = width;
		engineWindow->m_Height = height;

		Events::WindowResizedEvent e(width, height);
		engineWindow->m_EventCallbackFn(e);
	}

	void windowCloseCallback(GLFWwindow* glfwWindow) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		Events::WindowClosedEvent e;
		engineWindow->m_EventCallbackFn(e);
	}

	void windowPositionCallback(GLFWwindow* glfwWindow, int32_t xpos, int32_t ypos) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		Events::WindowMovedEvent e(static_cast<float>(xpos), static_cast<float>(ypos));
		engineWindow->m_EventCallbackFn(e);
	}

	void windowFocusCallback(GLFWwindow* glfwWindow, int32_t focused) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		if (focused == GLFW_TRUE) {
			Events::WindowFocusGainedEvent e;
			engineWindow->m_EventCallbackFn(e);
		}
		else {
			Events::WindowFocusLostEvent e;
			engineWindow->m_EventCallbackFn(e);
		}
	}

	void framebufferSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		engineWindow->m_Width = width;
		engineWindow->m_Height = height;

		glViewport(0, 0, engineWindow->m_Width, engineWindow->m_Height);
	}

	void keyCallback(GLFWwindow* glfwWindow, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		static int32_t previousKey = -1, repeatCount = 0;

		switch (action) {
			case GLFW_PRESS: {
				repeatCount = 0;
				previousKey = key;
				Events::KeyPressedEvent e(static_cast<Inputs::KeyCode>(key));
				engineWindow->m_EventCallbackFn(e);
				break;
			}
			case GLFW_RELEASE: {
				Events::KeyReleasedEvent e(static_cast<Inputs::KeyCode>(key));
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
				Events::KeyRepeatEvent e(static_cast<Inputs::KeyCode>(key), repeatCount);
				engineWindow->m_EventCallbackFn(e);
				break;
			}
		}

	}

	void mouseButtonCallback(GLFWwindow* glfwWindow, int32_t button, int32_t action, int32_t mods) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		
		switch (action) {
			case GLFW_PRESS: {
				Events::MouseButtonPressedEvent e(static_cast<Inputs::MouseCode>(button));
				engineWindow->m_EventCallbackFn(e);
				break;
			}
			case GLFW_RELEASE: {
				Events::MouseButtonReleasedEvent e(static_cast<Inputs::MouseCode>(button));
				engineWindow->m_EventCallbackFn(e);
				break;
			}
		}
	}

	void mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		Events::MouseWheelScrolledEvent e(static_cast<float>(xoffset), static_cast<float>(yoffset));
		engineWindow->m_EventCallbackFn(e);
	}

	void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		Events::MouseMovedEvent e(static_cast<float>(xpos), static_cast<float>(ypos));
		engineWindow->m_EventCallbackFn(e);
	}
}