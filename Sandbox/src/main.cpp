/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Graphics/Shader.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Maths;
	using namespace Graphics;
	using namespace Utils;

	Window window(800, 600, "Hart Engine: Sandbox", true);
	Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		window.handleEvents();
		window.update();
		window.clear();
		
		

		window.swapBuffers();
	}
	
	return 0;
}