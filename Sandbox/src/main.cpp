/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Application.hpp"

int main() {

	using namespace Hart;
	Application app(640, 480, "Sandbox");

	while (app.isRunning()) {
		app.handleEvents();
		app.update();
		app.render();
	}

	return 0;
}