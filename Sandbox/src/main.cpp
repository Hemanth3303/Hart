/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Application.hpp"

int main() {

	Hart::Application app(640, 480, "Sandbox", true);

	while (app.isRunning()) {
		app.handleEvents();
		app.update();
		app.render();
	}

	return 0;
}