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
#include "InputCodes/KeyCodes.hpp"

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

		void eventCallback(Event& e);

		// Event managers
		bool onWindowResized(WindowResizedEvent& e);
		bool onWindowClosed(WindowClosedEvent& e);
		bool onWindowMoved(WindowMovedEvent& e);
		bool onKeyPressed(KeyPressedEvent& e);

		static void LogCompileInfo();
	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ShaderLibrary m_ShaderLibrary;
		bool m_IsRunning = false;
		KeyCode m_ExitKey = KeyCode::Unknown;
		double m_CurrentFPS = 0.0;
		uint64_t m_LastFrameTime = 0.0;
		bool m_IsVsyncEnabled = false;
		bool m_IsWindowMinimized = false;

	private:
		// initializes engine's shader library with some defaul shaders
		// must be called before Renderer3D::Init() and Renderer2D::Init()
		void initializeShaderLibrary();
	};

	// User must define this function
	// Return a std::unique_ptr to Derived using the syntax std::make_unique<Derived>(args_if_they_exist), where Derived is a class derived from Hart::Application
	std::unique_ptr<Application> CreateApplication();
}
