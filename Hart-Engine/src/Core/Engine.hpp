#pragma once

#include "HartPch.hpp"
#include "Window.hpp"

namespace Hart {
	//temp
	//TODO: Remove this at implementation of scene class
	using Scene = int;
	class Engine {
	public:
		static void Init(int32_t windowWidth = 800, int windowHeight = 600, const std::string& windowTitle = "Hart Engine: Sandbox", bool resizable = false);
		static void HandleEvents();
		static void Update();
		static void Render();
		static void DeInit();

		static void AddScene(/*Scene& scene*/);
		static void RemeoveScene(/*Scene& scene*/);
		static void SetAsActiveScene(/*Scene& scene*/);

		static inline const bool IsRunning() { return !glfwWindowShouldClose(m_Window->getGlfwWindow()); }
	private:
		static Window* m_Window;
		static std::unordered_map<std::string, Scene> m_Scenes;
		static Scene* m_ActiveScene;
	};
}