#pragma once

#include "Window.hpp"
#include "Layer.hpp"
#include "LayerStack.hpp"
#include "Maths/Vec2.hpp"
#include "Graphics/ShaderLibrary.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/EventCategory.hpp"
#include "Inputs/KeyCodes.hpp"

namespace Hart {
	// Base class representing an application/game made using Hart.
	// The user must extend from this class and override some methods to make an app/game
	// Methods available to override:
	//		void onEvent(const Event& e): optional
	//		void update(const double deltaTime): compulsory
	//		void render(): compulsory
	class Application {
	public:
		Application();
		// takes window configurations as arguments
		Application(int32_t windowWidth, int32_t windowHeight, const std::string& windowTitle, bool isWindowResizable = false);
		virtual ~Application();

		// enables or disables vsync
		void enableVsync(bool enable = true);
		// main engine loop
		void run();
		// sets OpenGL clear color
		// rgba values in range 0 to 1
		void setBackgroundColor(const Vec4& color);

		// getters

		// returns a non owning reference to the current static application instance
		inline static Application* const& Get() { return s_Instance; }
		// returns a non ownning pointer to the Hart::Window object
		inline const Window* getWindow() const { return m_Window.get(); }
		inline const int32_t getWindowWidth() const { return m_Window->getWidth(); }
		inline const int32_t getWindowHeight() const { return m_Window->getHeight(); }
		inline const Vec2 getWindowDimensions() const { return m_Window->getDimensions(); }
		inline const double getCurrentFPS() { return m_CurrentFPS; }
		inline bool isVsyncEnabled() const { return m_IsVsyncEnabled; }
		inline bool isWindowMinimized() const { return m_IsWindowMinimized; }
		inline std::shared_ptr<Shader> getShader(const std::string& name) { return m_ShaderLibrary.getShader(name); }
		inline std::vector<std::string_view> getAllShaderNames() { return m_ShaderLibrary.getAllShaderNames(); }

		// setters

		// sets the maximum frames per second
		// default value is 1000
		inline void setMaxFPS(double maxFPS) { m_MaxFPS = maxFPS; }
		inline void setExitKey(const KeyCode& exitKey) { m_ExitKey = exitKey; }

	protected:
		void pushLayer(const std::shared_ptr<Layer>& layer);
		void popLayer(const std::shared_ptr<Layer>& layer);
		void pushOverlay(const std::shared_ptr<Layer>& overlay);
		void popOverlay(const std::shared_ptr<Layer>& overlay);

		inline bool layerExists(const std::string& layerName) { return m_LayerStack.layerExists(layerName); }
		inline bool overlayExists(const std::string& overlayName) { return m_LayerStack.overlayExists(overlayName); }
		inline const std::shared_ptr<Layer> getLayer(const std::string& layerName) { return m_LayerStack.getLayer(layerName); }
		inline const std::shared_ptr<Layer> getOverlay(const std::string& overlayName) { return m_LayerStack.getOverlay(overlayName); }

	private:
		// initializes application
		void init(const WindowProps& windowProps);
		// deinitializes application
		void deinit();

		// Event managers
		void eventHandler(Event& e);
		// Begin Event Methods
		// The methods below return true if the event is processed and no need to propogate further, else they return false

		// window
		bool onWindowResized(WindowResizedEvent& e);
		bool onWindowClosed(WindowClosedEvent& e);
		bool onWindowMoved(WindowMovedEvent& e);
		bool onWindowFocusGained(WindowFocusGainedEvent& e);
		bool onWindowFocusLost(WindowFocusLostEvent& e);

		// keyboard
		bool onKeyPressed(KeyPressedEvent& e);
		bool onKeyReleased(KeyReleasedEvent& e);
		bool onKeyRepeat(KeyRepeatEvent& e);

		// mouse
		bool onMouseMoved(MouseMovedEvent& e);
		bool onMouseWheelScrolled(MouseWheelScrolledEvent& e);
		bool onMouseButtonPressed(MouseButtonPressedEvent& e);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e);
		// End Event Methods
	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ShaderLibrary m_ShaderLibrary;
		bool m_IsRunning = false;
		KeyCode m_ExitKey = KeyCode::Unknown;
		double m_MaxFPS = 1'000, m_CurrentFPS = 0.0;
		uint64_t m_LastFrameTime = 0.0;
		bool m_IsVsyncEnabled = false;
		bool m_IsWindowMinimized = false;

	private:
		// initializes engine's shader library with some defaul shaders
		friend void initializeShaderLibrary();
		// based on https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f
		friend void OpenGLDebugMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParameter);
	};

	// User must define this function
	// Return a std::unique_ptr to Derived using the syntax std::make_unique<Derived>(args_if_they_exist), where Derived is a class derived from Hart::Application
	std::unique_ptr<Application> CreateApplication();
}
