/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Graphics/Shader.hpp"
#include "Maths/Mat4.hpp"

int main(int argc, char** argv) {

	Hart::Window window(640, 480, "HART ENGINE: SANDBOX", false);
	Hart::Graphics::Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		window.handleEvents();
		window.update();

		window.clear();
		//draw calls

		window.swapBuffers();
	}
	
	return 0;
}