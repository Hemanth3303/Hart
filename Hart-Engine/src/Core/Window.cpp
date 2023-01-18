#include "HartPch.hpp"
#include "Window.hpp"

namespace Hart {

	Window* Window::s_Instance;

	Window::Window(int32_t width, int32_t height, const std::string& title, bool resizable)
		:m_Width(width), m_Height(height), m_Title(title), m_Resizable(resizable) {
		init();

		HART_ASSERT_NOT_EQUAL(m_Window, nullptr);
		s_Instance = this;
	}

	Window::~Window() {
		HART_ENGINE_INFO("Closing GLFW");
		glfwTerminate();
		HART_ENGINE_INFO("Closing Window");
	}

	void Window::init() {
		glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
		HART_ENGINE_INFO("Initializing Window");
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		HART_ASSERT_NOT_EQUAL(m_Window, nullptr);
		HART_ENGINE_INFO("Window initialized successfully");
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, static_cast<void*>(this));

		int32_t success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HART_ASSERT_NOT_EQUAL(success, -1);
		HART_ENGINE_INFO("GLAD loaded successfully");

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, m_Width, m_Height);
	}

	void Window::setMousePosition(const Maths::Vec2& position) const {
		glfwSetCursorPos(m_Window, static_cast<double>(position.x), static_cast<double>(position.y));
	}
}