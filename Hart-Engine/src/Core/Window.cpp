#include "HartPch.hpp"
#include "Window.hpp"

namespace Hart {
	Window::Window(int32_t width, int32_t height, const std::string& title, bool resizable)
		:m_Width(width), m_Height(height), m_Title(title), m_Resizable(resizable) {

	}

	Window::~Window() {
		HART_ENGINE_INFO("Closing GLFW");
		glfwTerminate();
		HART_ENGINE_INFO("Closing Window");
	}

	void Window::init() {
		HART_ENGINE_INFO("Initializing GLFW");
		int32_t success = glfwInit();
		HART_ASSERT_EQUAL(success, GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
		HART_ENGINE_INFO("GLFW initialized successfully");

		HART_ENGINE_INFO("Initializing Window");
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		HART_ASSERT_NOT_EQUAL(m_Window, nullptr);
		HART_ENGINE_INFO("Window initialized successfully");
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, static_cast<void*>(this));
		glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);

		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HART_ASSERT_NOT_EQUAL(success, -1);
		HART_ENGINE_INFO("GLAD loaded successfully");

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, m_Width, m_Height);
	}

	void framebufferSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		engineWindow->m_Width = width;
		engineWindow->m_Height = height;
		glViewport(0, 0, engineWindow->m_Width, engineWindow->m_Height);
	}
}