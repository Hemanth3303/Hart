#include "Core/HartPch.hpp"
#include "Engine.hpp"

namespace Hart {

	bool Engine::m_IsRunning = false;

	void Engine::Init() {
		HART_ENGINE_INFO("Initialising Engine");
	}

	void Engine::DeInit() {
		HART_ENGINE_INFO("Shutting down Engine");
	}

	void Engine::Update() {
		HART_ENGINE_INFO("Update loop");
	}

	const bool& Engine::Running() {
		return m_IsRunning;
	}

}