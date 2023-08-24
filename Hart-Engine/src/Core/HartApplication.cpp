#include "HartPch.hpp"
#include "HartApplication.hpp"
#include "Base.hpp"
#include "Utils/Timer.hpp"
#include "Inputs/InputManager.hpp"
#include "Graphics/Renderer/RenderCommand.hpp"
#include "Graphics/Renderer/Renderer3D.hpp"
#include "Graphics/Renderer/Renderer2D.hpp"

namespace Hart {

	Application* Application::s_Instance = nullptr;

	extern void initializeShaderLibrary();

	// based on https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f
	void OpenGLDebugMessageCallback(std::uint32_t source, std::uint32_t type, std::uint32_t id, std::uint32_t severity, std::int32_t length, const char* message, const void* userParameter);

	Application::Application() 
		:m_WindowData() {
		init();
	}

	Application::Application(std::int32_t windowWidth, std::int32_t windowHeight, const std::string& windowTitle, bool isWindowResizable) 
		:m_WindowData(windowWidth, windowHeight, windowTitle, isWindowResizable) {
		init();
	}

	Application::~Application() {
		deinit();
		HART_ENGINE_LOG("Shutting down Hart Engine");
	}

	void Application::run() {
		HART_ENGINE_LOG("Entering main engine loop");

		double maxPeriod = 1.0f / m_MaxFPS;
		double currentFrameTime = Timer::GetTimeInMilliSeconds();
		double deltaTime = 0.0;

		while (m_IsRunning) {

			if (InputManager::IsKeyPressed(m_ExitKey)) {
				m_IsRunning = false;
			}

			glfwPollEvents();
			
			currentFrameTime = Timer::GetTimeInMilliSeconds();
			deltaTime = (currentFrameTime - m_LastFrameTime) / 1000.0;
			
			if (deltaTime >= maxPeriod) {
				m_LastFrameTime = currentFrameTime;
				m_CurrentFPS = 1.0 / deltaTime;

				// update
				for (const auto& layer : m_LayerStack) {
					layer->update(static_cast<float>(deltaTime));
				}

				//render
				RenderCommand::Clear();
				for (const auto& layer : m_LayerStack) {
					layer->render();
				}
				m_Window->swapBuffers();
			}
		}
		HART_ENGINE_LOG("Exiting main engine loop");
	}

    void Application::setBackgroundColor(const Vec4& color) {
		RenderCommand::SetClearColor(color);
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

	void Application::init() {
		HART_ENGINE_LOG(
			"Compilation Information:", 
			"\t\t\t\t\tCompiled using: " HART_COMPILER " | Version: " HART_COMPILER_VERSION,
			"\t\t\t\t\tCompiled On: " HART_COMPILATION_TIMESTAMP,
			"\t\t\t\t\tOn Platform: " HART_PLATFORM
		);


		HART_ENGINE_LOG("Initializing Hart Engine");

		s_Instance = this;
		HART_ASSERT_NOT_EQUAL(s_Instance, nullptr);

		HART_ENGINE_LOG("Initializing GLFW");
		std::int32_t success = glfwInit();
		HART_ASSERT_EQUAL(success, GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
	#if defined(HART_DEBUG) || defined(HART_RELEASE)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	#endif // defined(HART_DEBUG) || defined(HART_RELEASE)


		glfwSwapInterval(0);
		HART_ENGINE_LOG("GLFW initialized successfully");

		m_Window = std::make_unique<Window>(m_WindowData);
		m_IsRunning = true;

	#if defined(HART_DEBUG) || defined(HART_RELEASE)
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLDebugMessageCallback, nullptr);
	#endif // defined(HART_DEBUG) || defined(HART_RELEASE)

		initializeShaderLibrary();

		Timer::Init();
		InputManager::Init();
		Renderer3D::Init();

		m_Window->setEventCallback((BIND_EVENT_FUNC(Application::eventHandler)));

		// Setting clear color as black
		RenderCommand::SetClearColor(Black);
	}

	void Application::deinit() {
		m_LayerStack.popAll();
		Renderer3D::DeInit();
		InputManager::DeInit();
		Timer::DeInit();
		// i just want to see the "shutting down hart engine" message at last o_o
		m_Window.reset();

		HART_ENGINE_LOG("DeInitilizing GLFW");
		glfwTerminate();
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

		//pass events to layers
		for (auto itr = m_LayerStack.rbegin(); itr != m_LayerStack.rend(); itr++) {
			if (e.getHandled()) {
				break;
			}
			(*itr)->onEvent(e);
		}
	}
	
	bool Application::onWindowResized(WindowResizedEvent& e) {

		if (e.getWidth() == 0 || e.getHeight() == 0) {
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

	// based on https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f
	void OpenGLDebugMessageCallback(std::uint32_t source, std::uint32_t type, std::uint32_t id, std::uint32_t severity, std::int32_t length, const char* message, const void* userParameter) {
		const char* debugSource;
		const char* debugType;
		const char* debugSeverity;

		switch (source) {
			case GL_DEBUG_SOURCE_API:
				debugSource = "API";
				break;

			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				debugSource = "WINDOW SYSTEM";
				break;

			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				debugSource = "SHADER COMPILER";
				break;

			case GL_DEBUG_SOURCE_THIRD_PARTY:
				debugSource = "THIRD PARTY";
				break;

			case GL_DEBUG_SOURCE_APPLICATION:
				debugSource = "APPLICATION";
				break;

			case GL_DEBUG_SOURCE_OTHER:
				debugSource = "UNKNOWN";
				break;

			default:
				debugSource = "UNKNOWN";
				break;
		}

		switch (type) {
			case GL_DEBUG_TYPE_ERROR:
				debugType = "ERROR";
				break;

			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				debugType = "DEPRECATED BEHAVIOR";
				break;

			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				debugType = "UDEFINED BEHAVIOR";
				break;

			case GL_DEBUG_TYPE_PORTABILITY:
				debugType = "PORTABILITY";
				break;

			case GL_DEBUG_TYPE_PERFORMANCE:
				debugType = "PERFORMANCE";
				break;

			case GL_DEBUG_TYPE_OTHER:
				debugType = "OTHER";
				break;

			case GL_DEBUG_TYPE_MARKER:
				debugType = "MARKER";
				break;

			default:
				debugType = "UNKNOWN";
				break;
		}

		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:
				debugSeverity = "HIGH";
				HART_ENGINE_FATAL(
					"OpenGL Error: ",
					std::string("\t\t\t\t\t\t  From: ") + std::string(debugSource),
					std::string("\t\t\t\t\t\t  Type: ") + std::string(debugType),
					std::string("\t\t\t\t\t\t  OpenGL Severity: ") + std::string(debugSeverity),
					std::string("\t\t\t\t\t\t  OpenGL Message: ") + std::string(message),
					);
				break;

			case GL_DEBUG_SEVERITY_MEDIUM:
				debugSeverity = "MEDIUM";
				HART_ENGINE_ERROR(
					"OpenGL Error: ",
					std::string("\t\t\t\t\t\t  From: ") + std::string(debugSource),
					std::string("\t\t\t\t\t\t  Type: ") + std::string(debugType),
					std::string("\t\t\t\t\t\t  OpenGL Severity: ") + std::string(debugSeverity),
					std::string("\t\t\t\t\t\t  OpenGL Message: ") + std::string(message),
				);
				break;

			case GL_DEBUG_SEVERITY_LOW:
				debugSeverity = "LOW";
				HART_ENGINE_WARNING(
					"OpenGL Error: ",
					std::string("\t\t\t\t\t\t  From: ") + std::string(debugSource),
					std::string("\t\t\t\t\t\t  Type: ") + std::string(debugType),
					std::string("\t\t\t\t\t\t  OpenGL Severity: ") + std::string(debugSeverity),
					std::string("\t\t\t\t\t\t  OpenGL Message: ") + std::string(message),
					);
				break;

			case GL_DEBUG_SEVERITY_NOTIFICATION:
				debugSeverity = "NOTIFICATION";
				HART_ENGINE_LOG(
					"OpenGL Error: ",
					std::string("\t\t\t\t\t\t  From: ") + std::string(debugSource),
					std::string("\t\t\t\t\t\t  Type: ") + std::string(debugType),
					std::string("\t\t\t\t\t\t  OpenGL Severity: ") + std::string(debugSeverity),
					std::string("\t\t\t\t\t\t  OpenGL Message: ") + std::string(message),
					);
				break;

			default:
				debugSeverity = "UNKNOWN";
				HART_ENGINE_ERROR(
					"OpenGL Error: ",
					std::string("\t\t\t\t\t\t  From: ") + std::string(debugSource),
					std::string("\t\t\t\t\t\t  Type: ") + std::string(debugType),
					std::string("\t\t\t\t\t\t  OpenGL Severity: ") + std::string(debugSeverity),
					std::string("\t\t\t\t\t\t  OpenGL Message: ") + std::string(message),
					);
				break;
		}
	}
}