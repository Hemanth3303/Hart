#include "HartPch.hpp"
#include "Application.hpp"
#include "Base.hpp"
#include "Assert.hpp"
#include "Utils/Timer.hpp"
#include "Utils/Logger.hpp"
#include "Inputs/InputManager.hpp"
#include "Graphics/OpenGLRenderer/OpenGLRenderer.hpp"
#include "Graphics/OpenGLRenderer/OpenGLRendererDebug.hpp"
#include "Graphics/Renderer3D/Renderer3D.hpp"
#include "Graphics/Renderer2D/Renderer2D.hpp"
#include "Graphics/EngineShaders/QuadShader2D.hpp"
#include "Graphics/EngineShaders/TextShader2D.hpp"
#include "Graphics/EngineShaders/CubeShader3D.hpp"

namespace Hart {
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		WindowProps windowProps;
		init(windowProps);
	}

	Application::Application(int32_t windowWidth, int32_t windowHeight, const std::string& windowTitle, bool isWindowResizable) {
		WindowProps windowProps;
		windowProps.width = windowWidth;
		windowProps.height = windowHeight;
		windowProps.title = windowTitle;
		windowProps.resizable = isWindowResizable;

		init(windowProps);
	}

	Application::~Application() {
		deinit();
		HART_ENGINE_INFO("Shutting down Hart Engine");
	}

	void Application::run() {
		HART_ENGINE_INFO("Entering main engine loop");

		m_LastFrameTime = Timer::GetTimepointNanoseconds();
		uint64_t currentFrameTime = Timer::GetTimepointNanoseconds();
		double deltaTime = 0.0;

		while (m_IsRunning) {

			if (InputManager::IsKeyPressed(m_ExitKey)) {
				HART_ENGINE_TRACE("ExitKey(GLFW_KEY_CODE = ", (int)m_ExitKey, ") was pressed.");
				m_IsRunning = false;
			}

			glfwPollEvents();

			currentFrameTime = Timer::GetTimepointNanoseconds();
			deltaTime = (currentFrameTime - m_LastFrameTime) / 1'000'000'000.0;

			m_LastFrameTime = currentFrameTime;
			m_CurrentFPS = 1.0 / deltaTime;

			// update
			for (const auto& layer : m_LayerStack) {
				layer->update(static_cast<float>(deltaTime));
			}

			// render
			OpenGLRenderer::Clear(
				RenderClearFlags::ColorBuffer |
				RenderClearFlags::DepthBuffer |
				RenderClearFlags::StencilBuffer);

			for (const auto& layer : m_LayerStack) {
				layer->render();
			}
			m_Window->swapBuffers();
		}
		HART_ENGINE_INFO("Exiting main engine loop");
	}

	void Application::setBackgroundColor(const Vec4& color) {
		OpenGLRenderer::SetClearColor(color);
	}

	void Application::enableVsync(bool enable) {
		if (!enable) {
			m_IsVsyncEnabled = false;
			glfwSwapInterval(0);
		}
		else {
			m_IsVsyncEnabled = true;
			glfwSwapInterval(1);
		}
	}

	void Application::pushLayer(const std::shared_ptr<Layer>& layer) {
		m_LayerStack.pushLayer(layer);
	}

	void Application::popLayer(const std::shared_ptr<Layer>& layer) {
		m_LayerStack.popLayer(layer);
	}

	void Application::pushOverlay(const std::shared_ptr<Layer>& overlay) {
		m_LayerStack.pushOverlay(overlay);
	}

	void Application::popOverlay(const std::shared_ptr<Layer>& overlay) {
		m_LayerStack.popOverlay(overlay);
	}

	void Application::init(const WindowProps& windowProps) {
		HART_ENGINE_INFO(
			"\n\t\t\t===============Compilation Information===============",
			"\n\t\t\t\tCompiled using: " HART_COMPILER_STR " | Version: " HART_COMPILER_VERSION_STR,
			"\n\t\t\t\tCompiled On: " HART_COMPILATION_TIMESTAMP,
			"\n\t\t\t\tPlatform: " HART_PLATFORM_STR,
			"\n\t\t\t\tArchitecture: " HART_ARCHITECTURE_STR
			"\n\t\t\t=====================================================");

		HART_ENGINE_INFO("Initializing Hart Engine");

		s_Instance = this;
		HART_DEBUG_ASSERT((s_Instance != nullptr), "Reason: Failed to initialize Hart Engine");

		HART_ENGINE_INFO("Initializing GLFW");
		int32_t success = glfwInit();
		HART_DEBUG_ASSERT((success == GLFW_TRUE), "Reason: Failed to initialize GLFW");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(HART_ENGINE_DEBUG_BUILD) || defined(HART_ENGINE_PROFILE_BUILD)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

		HART_ENGINE_INFO("GLFW initialized successfully");

		m_Window = std::make_unique<Window>(windowProps);
		glfwSwapInterval(0);
		m_IsRunning = true;

		InputManager::Init();

		OpenGLRenderer::Init();
#if defined(HART_ENGINE_DEBUG_BUILD) || defined(HART_ENGINE_PROFILE_BUILD)
		OpenGLRendererDebug::Init();
#endif

		initializeShaderLibrary();
		Renderer2D::Init();
		Renderer3D::Init();

		m_Window->setEventCallback((BIND_EVENT_FUNC(Application::eventHandler)));

		// Setting clear color as black
		OpenGLRenderer::SetClearColor(Black);
	}

	void Application::deinit() {
		m_LayerStack.popAll();
		OpenGLRendererDebug::DeInit();
		Renderer3D::DeInit();
		Renderer2D::DeInit();
		OpenGLRenderer::DeInit();
		InputManager::DeInit();
		m_ShaderLibrary.clear();
		// i just want to see the "shutting down hart engine" message at last o_o
		m_Window.reset();

		HART_ENGINE_INFO("DeInitializing GLFW");
		glfwTerminate();

		s_Instance = nullptr;
	}

	void Application::eventHandler(Event& e) {

		EventDispatcher eventDispatcher(e);
		// window events
		eventDispatcher.dispatch<WindowResizedEvent>(BIND_EVENT_FUNC(Application::onWindowResized));
		eventDispatcher.dispatch<WindowClosedEvent>(BIND_EVENT_FUNC(Application::onWindowClosed));
		eventDispatcher.dispatch<WindowMovedEvent>(BIND_EVENT_FUNC(Application::onWindowMoved));
		eventDispatcher.dispatch<WindowFocusGainedEvent>(BIND_EVENT_FUNC(Application::onWindowFocusGained));
		eventDispatcher.dispatch<WindowFocusLostEvent>(BIND_EVENT_FUNC(Application::onWindowFocusLost));

		// key events
		eventDispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(Application::onKeyPressed));
		eventDispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(Application::onKeyReleased));
		eventDispatcher.dispatch<KeyRepeatEvent>(BIND_EVENT_FUNC(Application::onKeyRepeat));

		// mouse events
		eventDispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(Application::onMouseMoved));
		eventDispatcher.dispatch<MouseWheelScrolledEvent>(BIND_EVENT_FUNC(Application::onMouseWheelScrolled));
		eventDispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(Application::onMouseButtonPressed));
		eventDispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(Application::onMouseButtonReleased));

		// pass events to layers
		for (auto itr = m_LayerStack.rbegin(); itr != m_LayerStack.rend(); itr++) {
			if (e.getHandled()) {
				break;
			}
			(*itr)->onEvent(e);
		}
	}

	bool Application::onWindowResized(WindowResizedEvent& e) {

		if (e.getWidth() == 0 && e.getHeight() == 0) {
			m_IsWindowMinimized = true;
		}
		else {
			m_IsWindowMinimized = false;
		}

		m_Window->setWindowSize(e.getWidth(), e.getHeight());
		return false;
	}

	bool Application::onWindowClosed(WindowClosedEvent& e) {
		m_IsRunning = false;
		return true;
	}

	bool Application::onWindowMoved(WindowMovedEvent& e) {
		m_Window->setWindowPosition(e.getXpos(), e.getYpos());
		return true;
	}

	bool Application::onWindowFocusGained(WindowFocusGainedEvent& e) {
		// TODO
		return false;
	}

	bool Application::onWindowFocusLost(WindowFocusLostEvent& e) {
		// TODO
		return false;
	}

	bool Application::onKeyPressed(KeyPressedEvent& e) {
		InputManager::SetKeyPressed(e.getKeyCode());
		return false;
	}

	bool Application::onKeyReleased(KeyReleasedEvent& e) {
		InputManager::SetKeyReleased(e.getKeyCode());
		return false;
	}

	bool Application::onKeyRepeat(KeyRepeatEvent& e) {
		InputManager::SetKeyPressed(e.getKeyCode());
		return false;
	}

	bool Application::onMouseMoved(MouseMovedEvent& e) {
		InputManager::UpdateMousePosition(Vec2(e.getXPos(), e.getYPos()));
		return false;
	}

	bool Application::onMouseWheelScrolled(MouseWheelScrolledEvent& e) {
		// TODO
		return false;
	}

	bool Application::onMouseButtonPressed(MouseButtonPressedEvent& e) {
		InputManager::SetMouseButtonPressed(e.getMouseButton());
		return false;
	}

	bool Application::onMouseButtonReleased(MouseButtonReleasedEvent& e) {
		InputManager::SetMouseButtonReleased(e.getMouseButton());
		return false;
	}

	void Application::initializeShaderLibrary() {
		m_ShaderLibrary.loadShaderFromString("QuadShader2D", QuadShader2DVertexSource.c_str(), QuadShader2DFragmentSource.c_str());
		m_ShaderLibrary.loadShaderFromString("TextShader", TextShaderVertexSource.c_str(), TextShaderFragmentSource.c_str());
		m_ShaderLibrary.loadShaderFromString("CubeShader3D", CubeShader3DVertexSource.c_str(), CubeShader3DFragmentSource.c_str());
	}
}
