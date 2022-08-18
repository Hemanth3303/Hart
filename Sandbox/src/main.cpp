#include "Core/Engine.hpp"

int main() {
	Hart::Engine::Init();

	while (Hart::Engine::Running()) {
		Hart::Engine::Update();
	}

	Hart::Engine::DeInit();
}