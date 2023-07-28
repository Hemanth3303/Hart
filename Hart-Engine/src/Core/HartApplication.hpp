#pragma once

#include "HartPch.hpp"
#include "WindowData.hpp"
#include "Window.hpp"
#include "Layer.hpp"
#include "LayerStack.hpp"
#include "Maths/Vec2.hpp"
#include "Graphics/ShaderLibrary.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/EventCategory.hpp"
#include "Inputs/KeyCodes.hpp"

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
		// sets OpenGL clear color
		// rgba values in range 0 to 255
		void setBackgroundColor(const Maths::Vec4& color);
		
		//getters
		
		// returns a non owning reference to the current static application instance
		inline static Application* const& Get() { return s_Instance; }
		// returns a non ownning pointer to the Hart::Window object
		inline const Window* getWindow() const { return m_Window.get(); }
		inline const std::int32_t getWindowWidth() const { return m_Window->getWidth(); }
		inline const std::int32_t getWindowHeight() const { return m_Window->getHeight(); }
		inline const double getCurrentFPS() { return m_CurrentFPS; }
		inline std::shared_ptr<Graphics::Shader> getShader(const std::string& name) { return m_ShaderLibrary.getShader(name); }
		inline std::vector<std::string_view> getAllShaderNames() { return m_ShaderLibrary.getAllShaderNames(); }

		//setters
		
		// sets the maximum frames per second
		// default value is 1000
		inline void setMaxFPS(double maxFPS) { m_MaxFPS = maxFPS; }
		inline void setExitKey(const Inputs::KeyCode& exitKey) { m_ExitKey = exitKey; }
		inline bool isVsyncEnabled() const { return m_IsVsyncEnabled; }
		inline bool isWindowMinimized() const { return m_IsWindowMinimized; }
	protected:
		void pushLayer(const std::shared_ptr<Layer>& layer);
		void popLayer(const std::shared_ptr<Layer>& layer);
		void pushOverlay(const std::shared_ptr<Layer>& overlay);
		void popOverlay(const std::shared_ptr<Layer>& overlay);
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
	private:
		static Application* s_Instance;
		WindowData m_WindowData;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		Graphics::ShaderLibrary m_ShaderLibrary;
		bool m_IsRunning = false;
		Inputs::KeyCode m_ExitKey = Inputs::KeyCode::Unknown;
		double m_MaxFPS = 1'000, m_CurrentFPS=0.0;
		double m_LastFrameTime = 0.0;
		bool m_IsVsyncEnabled = false;
		bool m_IsWindowMinimized = false;
	private:
		// initializes engine's shader library with some defaul shaders
		friend void initializeShaderLibrary();
	};

	// User must define this function
	// Return a std::unique_ptr to Derived using the syntax std::make_unique<Derived>(args_if_they_exist), where Derived is a class derived from Hart::Application
	std::unique_ptr<Application> CreateApplication();

}