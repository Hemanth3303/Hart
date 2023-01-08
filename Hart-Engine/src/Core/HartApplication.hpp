/*
* Base class representing an application/game made using Hart.
* The user must extend from this class and override some methods to make an app/game
*/

#pragma once

#include "HartPch.hpp"
#include "Window.hpp"
#include "WindowConfigs.hpp"

namespace Hart {
	class Application {
	public:
		Application();
		virtual ~Application();

		void run();
		// set the configurations with which the window is created.
		// has not effect if called outside the constructor of a child class of the application class
		void setWindowConfigs(int32_t width, int32_t height, const std::string& title, bool resizable);

		inline const int32_t getWindowWidth() const { return m_Window->getWidth(); }
		inline const int32_t getWindowHeight() const { return m_Window->getHeight(); }
	protected:
		//must be overriden by user
		virtual void update() = 0;
		//must be overriden by user
		virtual void render() = 0;
	private:
		void init();
		void deinit();
		void handleEvents();
	private:
		std::unique_ptr<Window> m_Window;
		WindowConfigs m_Configs;
		bool m_IsRunning = false;
	};

	Application* CreateApplication();
}