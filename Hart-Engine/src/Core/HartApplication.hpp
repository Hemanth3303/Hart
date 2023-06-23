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
#include "Inputs/KeyCodes.hpp"
#include "Graphics/Primitives/ShaderLibrary.hpp"

namespace Hart {
	// Base class representing an application/game made using Hart.
	// The user must extend from this class and override some methods to make an app/game
	// Methods available to override:
	//		void onEvent(const Events::Event& e): optional
	//		void update(const double deltaTime): compulsory
	//		void render(): compulsory
	class Application {
	public:
		Application();
		// takes window configurations as arguments
		Application(std::int32_t windowWidth, std::int32_t windowHeight, const std::string& windowTitle, bool isWindowResizable = false);
		virtual ~Application();

		// enables or disables vsync
		void enableVsync(bool enable = true);
		// main engine loop
		void run();

		// returns a non ownning pointer to the Hart::Window object
		inline const Window* getWindow() const { return m_Window.get(); }
		inline const std::int32_t getWindowWidth() const { return m_Window->getWidth(); }
		inline const std::int32_t getWindowHeight() const { return m_Window->getHeight(); }
		inline int64_t getMaxTextureSlotsPerShader() const { return s_MaxNoOfTextureSlotsPerShader; }
		inline const int64_t getMaxTextureSlotsCombined() const { return s_MAX_TEXURE_SLOTS_COMBINED; }
		inline bool isVsyncEnabled() const { return m_IsVsyncEnabled; }
		inline const double getCurrentFPS() { return m_CurrentFPS; }
		// sets the maximum frames per second
		// default value is 60
		inline void setMaxFPS(double maxFPS) { m_MaxFPS = maxFPS; }
		inline void setExitKey(const Inputs::KeyCode& exitKey) { m_ExitKey = exitKey; }
	protected:
		//can be overriden by user, default implementation does nothing
		virtual void onEvent(Events::Event& e) {}
		//must be overriden by user
		virtual void update(const float deltaTime) = 0;
		//must be overriden by user
		virtual void render() = 0;
	private:
		// initializes application
		void init();
		// deinitializes application
		void deinit();
		// Event managers
		void eventHandler(Events::Event& e);
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
		Inputs::KeyCode m_ExitKey = Inputs::KeyCode::Escape;
		bool m_IsVsyncEnabled = false;
		double m_MaxFPS = 60.0, m_CurrentFPS=0.0;
		double m_LastFrameTime = 0.0;

		static int64_t s_MaxNoOfTextureSlotsPerShader;
		static const int64_t s_MAX_TEXURE_SLOTS_COMBINED = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
	};

	// User must define this function
	// Return a std::unique_ptr to Derived using the syntax std::make_unique<Derived>(args_if_they_exist), where Derived is a class derived from Hart::Application
	std::unique_ptr<Application> CreateApplication();
}