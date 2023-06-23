#include "HartPch.hpp"
#include "HartApplication.hpp"
#include "Utils/Timer.hpp"
#include "Inputs/InputManager.hpp"
#include "Graphics/Renderer/RenderCommand.hpp"
#include "Graphics/Renderer/Renderer3D.hpp"

namespace Hart {

	Application* Application::s_Instance = nullptr;

	int64_t Application::s_MaxNoOfTextureSlotsPerShader;

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

		// Setting clear color as black
		Graphics::RenderCommand::SetClearColor(Maths::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

		while (m_IsRunning) {

			if (Inputs::InputManager::IsKeyPressed(m_ExitKey)) {
				m_IsRunning = false;
			}

			glfwPollEvents();
			
			double maxPeriod = 1.0f / m_MaxFPS;
			double currentFrameTime = Utils::Timer::getTimeInMilliSeconds();
			double deltaTime = (currentFrameTime - m_LastFrameTime) / 1000.0;
			
			if (deltaTime >= maxPeriod) {
				m_LastFrameTime = currentFrameTime;
				m_CurrentFPS = 1.0 / deltaTime;

				update(static_cast<float>(deltaTime));
				Graphics::RenderCommand::Clear();
				render();
				m_Window->swapBuffers();
			}
		}
		HART_ENGINE_LOG("Exiting main engine loop");
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

	void Application::init() {
		HART_ENGINE_LOG("COMPILED ON " __DATE__ " " __TIME__);
		HART_ENGINE_LOG("Initializing Hart Engine");

		s_Instance = this;
		HART_ASSERT_NOT_EQUAL(s_Instance, nullptr);

		Utils::Timer::Init();

		Inputs::InputManager::Init();

		HART_ENGINE_LOG("Initializing GLFW");
		std::int32_t success = glfwInit();
		HART_ASSERT_EQUAL(success, GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSwapInterval(0);
		HART_ENGINE_LOG("GLFW initialized successfully");

		m_Window = std::make_unique<Window>(m_WindowData);
		m_IsRunning = true;

		glGetInteger64v(GL_MAX_TEXTURE_IMAGE_UNITS, &s_MaxNoOfTextureSlotsPerShader);
		HART_ENGINE_LOG(std::string("Maximum texture slots per shader = ") + std::to_string(s_MaxNoOfTextureSlotsPerShader));
		HART_ENGINE_LOG(std::string("Maximum texture slots combined = ") + std::to_string(s_MAX_TEXURE_SLOTS_COMBINED));

		HART_ENGINE_LOG(
			"OpenGL Renderer Info:",
			std::string("\t\t\t\t\tVendor: ") + reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
			std::string("\t\t\t\t\tRenderer: ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
			std::string("\t\t\t\t\tVersion: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION))
		);

		Graphics::Renderer3D::Init();

		m_Window->setEventCallback((BIND_EVENT_FUNC(Application::eventHandler)));
	}

	void Application::deinit() {
		// i just want to see the "shutting down hart engine" message at last o_o
		m_Window.reset();
		Utils::Timer::DeInit();
	}

	void Application::eventHandler(Events::Event& e) {

		Events::EventDispatcher eventDispatcher(e);
		// window events
		eventDispatcher.dispatch<Events::WindowResizedEvent>(BIND_EVENT_FUNC(Application::onWindowResized));
		eventDispatcher.dispatch<Events::WindowClosedEvent>(BIND_EVENT_FUNC(Application::onWindowClosed));
		eventDispatcher.dispatch<Events::WindowMovedEvent>(BIND_EVENT_FUNC(Application::onWindowMoved));
		eventDispatcher.dispatch<Events::WindowFocusGainedEvent>(BIND_EVENT_FUNC(Application::onWindowFocusGained));
		eventDispatcher.dispatch<Events::WindowFocusLostEvent>(BIND_EVENT_FUNC(Application::onWindowFocusLost));

		// key events
		eventDispatcher.dispatch<Events::KeyPressedEvent>(BIND_EVENT_FUNC(Application::onKeyPressed));
		eventDispatcher.dispatch<Events::KeyReleasedEvent>(BIND_EVENT_FUNC(Application::onKeyReleased));
		eventDispatcher.dispatch<Events::KeyRepeatEvent>(BIND_EVENT_FUNC(Application::onKeyRepeat));

		// mouse events
		eventDispatcher.dispatch<Events::MouseMovedEvent>(BIND_EVENT_FUNC(Application::onMouseMoved));
		eventDispatcher.dispatch<Events::MouseWheelScrolledEvent>(BIND_EVENT_FUNC(Application::onMouseWheelScrolled));
		eventDispatcher.dispatch<Events::MouseButtonPressedEvent>(BIND_EVENT_FUNC(Application::onMouseButtonPressed));
		eventDispatcher.dispatch<Events::MouseButtonReleasedEvent>(BIND_EVENT_FUNC(Application::onMouseButtonReleased));

		//pass events to client
		onEvent(e);

	}
	
	bool Application::onWindowResized(Events::WindowResizedEvent& e) {
		m_Window->setWindowSize(e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onWindowClosed(Events::WindowClosedEvent& e) {
		m_IsRunning = false;
		return true;
	}

	bool Application::onWindowMoved(Events::WindowMovedEvent& e) {
		m_Window->setWindowPosition(e.getXpos(), e.getYpos());
		return true;
	}

	bool Application::onWindowFocusGained(Events::WindowFocusGainedEvent& e) {
		// TODO
		return false;
	}

	bool Application::onWindowFocusLost(Events::WindowFocusLostEvent& e) {
		// TODO
		return false;
	}

	bool Application::onKeyPressed(Events::KeyPressedEvent& e) {
		Inputs::InputManager::SetKeyPressed(e.getKeyCode());
		return true;
	}

	bool Application::onKeyReleased(Events::KeyReleasedEvent& e) {
		Inputs::InputManager::SetKeyReleased(e.getKeyCode());
		return true;
	}

	bool Application::onKeyRepeat(Events::KeyRepeatEvent& e) {
		Inputs::InputManager::SetKeyPressed(e.getKeyCode());
		return true;
	}

	bool Application::onMouseMoved(Events::MouseMovedEvent& e) {
		Inputs::InputManager::UpdateMousePosition(Maths::Vec2(e.getXPos(), e.getYPos()));
		return true;
	}

	bool Application::onMouseWheelScrolled(Events::MouseWheelScrolledEvent& e) {
		// TODO
		return false;
	}

	bool Application::onMouseButtonPressed(Events::MouseButtonPressedEvent& e) {
		Inputs::InputManager::SetMouseButtonPressed(e.getMouseButton());
		return true;
	}

	bool Application::onMouseButtonReleased(Events::MouseButtonReleasedEvent& e) {
		Inputs::InputManager::SetMouseButtonReleased(e.getMouseButton());
		return true;
	}
}