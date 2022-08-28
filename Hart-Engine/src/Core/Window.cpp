#include "HartPch.hpp"
#include "Window.hpp"

namespace Hart {

	Window::Window(int32_t width, int32_t height, const std::string& title) 
		:m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr) {

		init();
	}


	Window::~Window() {
		deinit();
	}


	void Window::init() {

	}


	void Window::handleEvents() {

	}


	void Window::update() {

	}

	void Window::deinit() {

	}

}