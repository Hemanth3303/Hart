#include "HartPch.hpp"
#include "HartApplication.hpp"


namespace Hart {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::run() {
		while (true) {
			update();
			render();
		}
	}
}