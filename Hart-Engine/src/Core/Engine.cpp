#include "HartPch.hpp"
#include "Engine.hpp"

namespace Hart {

	Window* Engine::m_Window = nullptr;
	std::unordered_map<std::string, Scene> Engine::m_Scenes;
	Scene* Engine::m_ActiveScene = nullptr;

	void Engine::Init(int32_t windowWidth, int windowHeight, const std::string& windowTitle, bool resizable) {
		HART_ENGINE_INFO("Engine Initialised");
		m_Window = new Window(windowWidth, windowHeight, windowTitle, resizable);
		HART_ASSERT_NOT_EQUALS(m_Window, nullptr);
	}

	void Engine::HandleEvents() {
		m_Window->handleEvents();
		m_ActiveScene->handleEvents();
	}

	void Engine::Update() {
		m_Window->update();
		m_ActiveScene->update();
	}

	void Engine::Render() {
		m_Window->clear();

		//All draw calls
		
		/*
		for(auto& renderable: Scene.getRenderables())
			Renderer::Submit(renerable);
		Renderer::Flush();
		*/

		m_Window->swapBuffers();
	}

	void Engine::DeInit() {
		delete m_Window;
		HART_ENGINE_INFO("Engine Shutdown");
	}

	void Engine::AddScene(Scene& scene, const std::string& name) {
		m_Scenes[name] = scene;
		if (m_ActiveScene == nullptr) {
			m_ActiveScene = &(m_Scenes[name]);
		}
	}

	void Engine::RemeoveScene(const std::string& name) {
		m_Scenes.erase(name);
	}

	void Engine::SetAsActiveScene(const std::string& name) {
		m_ActiveScene = &(m_Scenes[name]);
	}

}