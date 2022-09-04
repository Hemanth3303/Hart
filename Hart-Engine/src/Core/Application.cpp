#include "HartPch.hpp"
#include "Window.hpp"
#include "Application.hpp"

namespace Hart {

	Application::Application(int32_t width, int32_t height, const std::string& title, bool resizable) 
		:m_Window(width, height, title, resizable), m_IsRunning(true) {
		init();
	}

	Application::~Application() {
		deinit();
	}

	void Application::handleEvents() {
		m_Window.handleEvents();
	}

	void Application::update() {
		if (glfwWindowShouldClose(m_Window.getGlfwWindow())) {
			m_IsRunning = false;
		}

		m_Window.update();

		//other update calls

	}

	void Application::render() {
		m_Window.clear();

		//all draw calls

		m_Window.swapBuffers();
	}

	//private methods

	void Application::init() {
		HART_ENGINE_INFO("Initialized Engine");
	}

	void Application::deinit() {
		HART_ENGINE_INFO("Shutting Down Engine");
	}

}