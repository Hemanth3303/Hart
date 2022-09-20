#pragma once

#include "HartPch.hpp"
#include "Window.hpp"
#include "Scene.hpp"

namespace Hart {
	class Engine {
	public:
		static void Init(int32_t windowWidth = 800, int windowHeight = 600, const std::string& windowTitle = "Hart Engine: Sandbox", bool resizable = false);
		static void HandleEvents();
		static void Update();
		static void Render();
		static void DeInit();

		static void AddScene(Scene& scene, const std::string& name);
		static void RemeoveScene(const std::string& name);
		static void SetAsActiveScene(const std::string& name);

		static inline const bool IsRunning() { return !glfwWindowShouldClose(m_Window->getGlfwWindow()); }
	private:
		static Window* m_Window;
		static std::unordered_map<std::string, Scene> m_Scenes;
		static Scene* m_ActiveScene;
	};
}