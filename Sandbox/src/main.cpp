/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Engine.hpp"
#include "Core/Scene.hpp"
#include "Graphics/Shader.hpp"

int main(int argc, char** argv) {

	Hart::Engine::Init();
	Hart::Scene scene1;
	Hart::Scene scene2;
	
	Hart::Graphics::Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	Hart::Engine::AddScene(scene1, "test_scene_1");
	Hart::Engine::AddScene(scene2, "test_scene_2");

	while (Hart::Engine::IsRunning()) {
		Hart::Engine::HandleEvents();
		Hart::Engine::Update();
		Hart::Engine::Render();

		Hart::Engine::SetAsActiveScene("test_scene_2");
	}
	
	return 0;
}