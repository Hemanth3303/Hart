#include "HartPch.hpp"
#include "Application.hpp"
#include "Base.hpp"
#include "CompileInfo.hpp"
#include "Assert.hpp"
#include "Utils/Timer.hpp"
#include "Utils/Logger.hpp"
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
		LogCompileInfo();
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

		OpenGLRenderer::Init();
#if defined(HART_ENGINE_DEBUG_BUILD) || defined(HART_ENGINE_PROFILE_BUILD)
		OpenGLRendererDebug::Init();
#endif

		initializeShaderLibrary();
		Renderer2D::Init();
		Renderer3D::Init();

		m_Window->setEventCallback([this](Event& e) {
			this->eventHandler(e);
		});

		// Setting clear color as black
		OpenGLRenderer::SetClearColor(Black);
	}

	void Application::deinit() {
		m_LayerStack.popAll();
		Renderer3D::DeInit();
		Renderer2D::DeInit();
		OpenGLRendererDebug::DeInit();
		OpenGLRenderer::DeInit();
		m_ShaderLibrary.clear();
		// i just want to see the "shutting down hart engine" message at last o_o
		m_Window.reset();

		HART_ENGINE_INFO("DeInitializing GLFW");
		glfwTerminate();

		s_Instance = nullptr;
	}

	void Application::LogCompileInfo() {
		HART_ENGINE_INFO(
			"\n\t\t\t===============Compilation Information===============",
			"\n\t\t\t\tHart Engine Version: ", HART_ENGINE_VERSION,
			"\n\t\t\t\tCompiled using: ", HART_COMPILER_STR, " v", HART_COMPILER_VERSION_STR,
			"\n\t\t\t\tCompiled On: ", HART_COMPILATION_TIMESTAMP,
			"\n\t\t\t\tPlatform: ", HART_PLATFORM_STR,
			"\n\t\t\t\tArchitecture: ", HART_ARCHITECTURE_STR,
			"\n\t\t\t=====================================================");
	}

	void Application::eventHandler(Event& e) {

		EventDispatcher eventDispatcher(e);

		// window events
		eventDispatcher.dispatch<WindowResizedEvent>([this](WindowResizedEvent& e) {
			return this->onWindowResized(e);
		});
		eventDispatcher.dispatch<WindowClosedEvent>([this](WindowClosedEvent& e) {
			return this->onWindowClosed(e);
		});
		eventDispatcher.dispatch<WindowMovedEvent>([this](WindowMovedEvent& e) {
			return this->onWindowMoved(e);
		});
		// key events
		eventDispatcher.dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) {
			return this->onKeyPressed(e);
		});

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

	bool Application::onKeyPressed(KeyPressedEvent& e) {
		if (e.getKeyCode() == m_ExitKey) {
			HART_ENGINE_INFO("Exit request received (Keycode = ", static_cast<int>(m_ExitKey), ")");
			m_IsRunning = false;
			return true;
		}
		return false;
	}

	void Application::initializeShaderLibrary() {
		m_ShaderLibrary.loadShaderFromString("QuadShader2D", QuadShader2DVertexSource.c_str(), QuadShader2DFragmentSource.c_str());
		m_ShaderLibrary.loadShaderFromString("TextShader", TextShaderVertexSource.c_str(), TextShaderFragmentSource.c_str());
		m_ShaderLibrary.loadShaderFromString("CubeShader3D", CubeShader3DVertexSource.c_str(), CubeShader3DFragmentSource.c_str());
	}
}
