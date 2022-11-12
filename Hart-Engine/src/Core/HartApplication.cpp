#include "HartPch.hpp"
#include "HartApplication.hpp"

namespace Hart {
	Application::Application() {
		init();
	}

	Application::~Application() {
		deinit();
	}

	void Application::run() {
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