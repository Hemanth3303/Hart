/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"

int main() {

	Hart::Window window(640, 480, "Hart Engine: Sandbox", true);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (window.isRunning()) {
		window.handleEvents();
		window.update();
		window.render();
	}

	return 0;
}