/*
* Base class representing an application/game made using Hart.
* The user must extend from this class and override some methods to make an app/game
*/

#pragma once

#include "HartPch.hpp"
#include "Window.hpp"
#include "WindowConfigs.hpp"
#include "InputManager.hpp"
#include "Maths/Vec2.hpp"

namespace Hart {
	class Application {
	public:
		Application();
		// takes window configurations as arguments
		Application(int32_t windowWidth, int32_t windowHeight, const std::string& windowTitle, bool isWindowResizable);
		virtual ~Application();

		void run();

		inline const int32_t getWindowWidth() const { return m_Window->getWidth(); }
		inline const int32_t getWindowHeight() const { return m_Window->getHeight(); }
		inline const Maths::Vec2& getMousePositon() const { return m_Window->getMousePosition(); }
		inline void setMousePosition(const Maths::Vec2& position) const { m_Window->setMousePosition(position); }
		// sets the preffered frames per second
		inline void setTargetFPS(uint32_t targetFPS) { m_TargetFPS = targetFPS; }
		// sets the preffered updates per second
		inline void setTargetUPS(uint32_t targetUPS) { m_TargetUPS = targetUPS; }
		inline uint32_t getCurrentFPS() { return m_CurrentFPS; }
		inline uint32_t getCurrentUPS() { return m_CurrentUPS; }
		// Application closes if this key is pressed
		inline void setExitKey(Keyboard::Key key) { m_ExitKey = key; }
	protected:
		//must be overriden by user
		virtual void update() = 0;
		//must be overriden by user
		virtual void render() = 0;
	private:
		void init();
		void deinit();
		void handleEvents();
		// set the configurations with which the window is created.
		void setWindowConfigs(int32_t width, int32_t height, const std::string& title, bool resizable);
	private:
		std::unique_ptr<Window> m_Window;
		WindowConfigs m_Configs;
		bool m_IsRunning = false;
		uint32_t m_TargetFPS = 60, m_TargetUPS = 60;
		uint32_t m_CurrentFPS = 0, m_CurrentUPS = 0;
		Keyboard::Key m_ExitKey = Keyboard::Key::Unknown;
	};

	Application* CreateApplication();
}