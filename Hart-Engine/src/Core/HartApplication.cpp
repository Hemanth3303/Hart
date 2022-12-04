#include "HartPch.hpp"
#include "HartApplication.hpp"

namespace Hart {
	Application::Application() {
		HART_ENGINE_INFO("Initializing Hart Engine");
		init();
	}

	Application::~Application() {
		HART_ENGINE_INFO("Shutting down Hart Engine");
		deinit();
	}

	void Application::run() {
		HART_ENGINE_INFO("Entering main engine loop");
		while (m_IsRunning) {
			handleEvents();
			update();
			render();
		}
	}

	void Application::init() {
		m_IsRunning = true;
	}

	void Application::deinit() {

	}

	void Application::handleEvents() {

	}
}