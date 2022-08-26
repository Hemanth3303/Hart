#include "Core/HartPch.hpp"
#include "Engine.hpp"

namespace Hart {

	bool Engine::m_IsRunning = false;

	void Engine::Init() {
		std::cout << "Init" << "\n";
	}

	void Engine::DeInit() {
		std::cout << "DeInit" << "\n";
	}

	void Engine::Update() {

	}

	const bool& Engine::Running() {
		return m_IsRunning;
	}

}