#include "HartPch.hpp"
#include "HartApplication.hpp"
#include "Utils/Timer.hpp"

namespace Hart {
	Application::Application() {
		HART_ENGINE_INFO("Initializing Hart Engine");
	}

	Application::~Application() {
		HART_ENGINE_INFO("Shutting down Hart Engine");
	}

	void Application::run() {
		init();
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
		deinit();
	}

	void Application::setWindowConfigs(int32_t width, int32_t height, const std::string& title, bool resizable) {
		m_Configs.winWidth = width;
		m_Configs.winHeight = height;
		m_Configs.title = title;
		m_Configs.resiable = resizable;
	}

	void Application::init() {
		m_Window = std::make_unique<Window>(m_Configs.winWidth, m_Configs.winHeight, m_Configs.title, m_Configs.resiable);
		m_IsRunning = true;
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
}