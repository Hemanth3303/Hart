/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Engine.hpp"
#include "Utils/Logger.hpp"

using namespace Hart;
using namespace Utils;

int main() {

	Engine::Init();

	Engine::Update();
	HART_CLIENT_INFO("Game stuff");

	Engine::DeInit();

	std::cin.get();

	return 0;
}