/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"

#include "Maths/Maths.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Loggable.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;
	using namespace Hart::Utils;

	Window window(960, 540, "Hart Engine: Sandbox", true);

	window.enableVsync();

	Random rd;
	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}

		window.handleEvents();
		window.clear();
		//draw calls
		window.swapBuffers();
	}

	return 0;
}