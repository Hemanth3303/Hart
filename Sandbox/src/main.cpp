/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Engine.hpp"
#include "Graphics/Shader.hpp"

int main(int argc, char** argv) {

	Hart::Engine::Init();
	
	Hart::Graphics::Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	while (Hart::Engine::IsRunning()) {
		Hart::Engine::HandleEvents();
		Hart::Engine::Update();
		Hart::Engine::Render();
	}
	
	return 0;
}