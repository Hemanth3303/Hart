#include "HartPch.hpp"
#include "Window.hpp"

namespace Hart {

	Window* Window::INSTANCE;

	Window::Window(int32_t width, int32_t height, const std::string& title, const bool& resizable)
		:m_Width(width), m_Height(height), m_Title(title), m_Resizable(resizable), m_Window(nullptr) {
		
		init();
		INSTANCE = this;
		HART_ENGINE_INFO("Initialized Hart Window");

	}

	Window::~Window() {
		deinit();
	}

	//public methods
	void Window::handleEvents() {
		glfwPollEvents();

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(m_Window, true);
		}

	}

	void Window::update() {
		
	}

	void Window::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(m_Window);
	}

	//private methods
	void Window::init() {
		int32_t result;
		result = glfwInit();
		HART_ASSERT_EQUALS(result, GLFW_TRUE);
		HART_ENGINE_INFO("GLFW Initialized");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif // __APPLE__

		glfwWindowHint(GLFW_RESIZABLE, m_Resizable);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		HART_ASSERT_NOT_EQUALS(m_Window, nullptr);
		HART_ENGINE_INFO("Created a GLFW window");

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, static_cast<void*>(this));
		glfwSetFramebufferSizeCallback(m_Window, frameBufferSizeCallback);

		result=gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HART_ASSERT_NOT_EQUALS(result, false);

		glViewport(0, 0, m_Width, m_Height);
		glEnable(GL_DEPTH_TEST);
		//default clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Window::deinit() {
		glfwTerminate();
		HART_ENGINE_INFO("Closing Hart Window");
	}

	//functions
	void frameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) {
		Window* hartWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		HART_ASSERT_NOT_EQUALS(hartWindow, nullptr);

		hartWindow->m_Width = width;
		hartWindow->m_Height = height;
		glViewport(0, 0, hartWindow->m_Width, hartWindow->m_Height);
	}

}