#include "Engine.hpp"

namespace Hart {

	bool Engine::m_IsRunning = false;

	void Engine::Init() {
		puts("Engine Init\n");
	}

	void Engine::DeInit() {
		puts("Engine DeInit\n");
	}

	void Engine::Update() {

	}

	const bool& Engine::Running() {
		return m_IsRunning;
	}

}