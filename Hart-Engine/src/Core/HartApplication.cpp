#include "HartPch.hpp"
#include "HartApplication.hpp"
#include "Utils/Timer.hpp"

namespace Hart {
	Application::Application() {
		HART_ENGINE_INFO("Initializing Hart Engine");
		init();
	}

	Application::Application(int32_t windowWidth, int32_t windowHeight, const std::string& windowTitle, bool isWindowResizable) {
		HART_ENGINE_INFO("Initializing Hart Engine");
		setWindowConfigs(windowWidth, windowHeight, windowTitle, isWindowResizable);
		init();
	}

	Application::~Application() {
		deinit();
		HART_ENGINE_INFO("Shutting down Hart Engine");
	}

	void Application::run() {
		HART_ENGINE_INFO("Entering main engine loop");

		double timePerFrame = 1000000000 / m_TargetFPS;
		double timePerUpdate = 1000000000 / m_TargetUPS;

		double previousTime = Utils::Timer::getTimeInNanoSeconds();

		int32_t updates = 0;
		int32_t frames = 0;
		double lastCheck = Utils::Timer::getTimeInMilliSeconds();

		double deltaUPS = 0;
		double deltaFPS = 0;

		while (m_IsRunning) {

			double currentTime = Utils::Timer::getTimeInNanoSeconds();
			deltaUPS += (currentTime - previousTime) / timePerUpdate;
			deltaFPS += (currentTime - previousTime) / timePerFrame;
			previousTime = currentTime;

			// update loop
			if (deltaUPS >= 1) {
				handleEvents();
				update();
				updates++;
				deltaUPS--;
			}

			// render loop
			if (deltaFPS >= 1) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				render();
				glfwSwapBuffers(m_Window->getGLFWwindow());
				frames++;
				deltaFPS--;
			}

			if (Utils::Timer::getTimeInMilliSeconds() - lastCheck >= 1000) {
				lastCheck = Utils::Timer::getTimeInMilliSeconds();
				m_CurrentFPS = frames;
				m_CurrentUPS = updates;
				frames = 0;
				updates = 0;
			}
			
		}
	}

	void Application::setWindowConfigs(int32_t width, int32_t height, const std::string& title, bool resizable) {
		m_Configs.winWidth = width;
		m_Configs.winHeight = height;
		m_Configs.title = title;
		m_Configs.resiable = resizable;
	}

	void Application::init() {

		HART_ENGINE_INFO("Initializing GLFW");
		int32_t success = glfwInit();
		HART_ASSERT_EQUAL(success, GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSwapInterval(0);
		HART_ENGINE_INFO("GLFW initialized successfully");

		m_Window = std::make_unique<Window>(m_Configs.winWidth, m_Configs.winHeight, m_Configs.title, m_Configs.resiable);
		m_IsRunning = true;

		glfwSetFramebufferSizeCallback(m_Window->getGLFWwindow(), framebufferSizeCallback);
		glfwSetCursorPosCallback(m_Window->getGLFWwindow(), cursorPositionCallback);
	}

	void Application::deinit() {
		// i just want to see the "shutting down hart engine" message at last o_o
		m_Window.reset();
	}

	void Application::handleEvents() {
		if (glfwWindowShouldClose(m_Window->getGLFWwindow())) {
			m_IsRunning = false;
		}
		if (Keyboard::isKeyDown(m_ExitKey)) {
			m_IsRunning = false;
		}
		glfwPollEvents();
	}

	void framebufferSizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		engineWindow->m_Width = width;
		engineWindow->m_Height = height;
		glViewport(0, 0, engineWindow->m_Width, engineWindow->m_Height);
	}

	void cursorPositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos) {
		Window* engineWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		engineWindow->m_MousePos.x = static_cast<float>(xpos);
		engineWindow->m_MousePos.y = static_cast<float>(ypos);
	}

}