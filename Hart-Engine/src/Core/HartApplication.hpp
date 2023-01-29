/*
* Base class representing an application/game made using Hart.
* The user must extend from this class and override some methods to make an app/game
*/

#pragma once

#include "HartPch.hpp"
#include "Window.hpp"
#include "WindowConfigs.hpp"
#include "Maths/Vec2.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/EventCategory.hpp"

namespace Hart {
	class Application {
	public:
		Application();
		// takes window configurations as arguments
		Application(int32_t windowWidth, int32_t windowHeight, const std::string& windowTitle, bool isWindowResizable);
		virtual ~Application();

		void run();

		// returns a non ownning reference to the Hart::Window object
		inline const Window* getWindow() const { return m_Window.get(); }
		inline const int32_t getWindowWidth() const { return m_Window->getWidth(); }
		inline const int32_t getWindowHeight() const { return m_Window->getHeight(); }
		inline const Maths::Vec2& getMousePositon() const { return m_Window->getMousePosition(); }
		inline void setMousePosition(const Maths::Vec2& position) const { m_Window->setMousePosition(position); }
		// sets the preferred frames per second
		// default value is 60
		inline void setTargetFPS(uint32_t targetFPS) { m_TargetFPS = targetFPS; }
		// sets the preferred updates per second
		// default value is 60
		inline void setTargetUPS(uint32_t targetUPS) { m_TargetUPS = targetUPS; }
		inline uint32_t getCurrentFPS() { return m_CurrentFPS; }
		inline uint32_t getCurrentUPS() { return m_CurrentUPS; }
	protected:
		//must be overriden by user
		virtual void update() = 0;
		//must be overriden by user
		virtual void render() = 0;
	private:
		void init();
		void deinit();
		void onEvent(Events::Event& e);
		bool onWindowClosed(Events::WindowClosedEvent& e);

		// set the configurations with which the window is created.
		void setWindowConfigs(int32_t width, int32_t height, const std::string& title, bool resizable);
	public:
		static Application* s_Instance;
	private:
		std::unique_ptr<Window> m_Window;
		WindowConfigs m_Configs;
		bool m_IsRunning = false;
		uint32_t m_TargetFPS = 60, m_TargetUPS = 60;
		uint32_t m_CurrentFPS = 0, m_CurrentUPS = 0;
	};

	// Create an object of a class Inheriting Hart::Application as a raw pointer using 'new' and return this it.
	// No need to free the object, the engine takes care of it internally.
	Application* CreateApplication();
}