/*
* Base class representing an application/game made using Hart.
* The user must extend from this class and override some methods to make an app/game
*/

#pragma once

#include "HartPch.hpp"
#include "WindowData.hpp"
#include "Window.hpp"
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
		Application(int32_t windowWidth, int32_t windowHeight, const std::string& windowTitle, bool isWindowResizable = false);
		virtual ~Application();

		void run();

		// returns a non ownning reference to the Hart::Window object
		inline const Window* getWindow() const { return m_Window.get(); }
		inline const int32_t getWindowWidth() const { return m_Window->getWidth(); }
		inline const int32_t getWindowHeight() const { return m_Window->getHeight(); }
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
		// Event managers
		void onEvent(Events::Event& e);
		// Begin Event Methods
		// The methods below return true if the event is processed and no need to propogate further, else they return false

		// window
		bool onWindowResized(Events::WindowResizedEvent& e);
		bool onWindowClosed(Events::WindowClosedEvent& e);
		bool onWindowMoved(Events::WindowMovedEvent& e);
		bool onWindowFocusGained(Events::WindowFocusGainedEvent& e);
		bool onWindowFocusLost(Events::WindowFocusLostEvent& e);

		// keyboard
		bool onKeyPressed(Events::KeyPressedEvent& e);
		bool onKeyReleased(Events::KeyReleasedEvent& e);
		bool onKeyRepeat(Events::KeyRepeatEvent& e);

		// mouse
		bool onMouseMoved(Events::MouseMovedEvent& e);
		bool onMouseWheelScrolled(Events::MouseWheelScrolledEvent& e);
		bool onMouseButtonPressed(Events::MouseButtonPressedEvent& e);
		bool onMouseButtonReleased(Events::MouseButtonReleasedEvent& e);
		// End Event Methods
	public:
		static Application* s_Instance;
	private:
		WindowData m_WindowData;
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = false;
		uint32_t m_TargetFPS = 60, m_TargetUPS = 60;
		uint32_t m_CurrentFPS = 0, m_CurrentUPS = 0;
	};

	// User must define this function
	// Return a std::unique_ptr to Derived using the syntax std::make_unique<Derived>(args_if_they_exist), where Derived is a class derived from Hart::Application
	std::unique_ptr<Application> CreateApplication();
}