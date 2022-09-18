/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Application.hpp"
#include "Core/Input.hpp"

int main(int argc, char** argv) {

	Hart::Application app(960, 600, "Hart Engine: Sandbox", true);

	while (app.isRunning()) {
		app.handleEvents();
		app.update();
		app.render();
	}
	
	return 0;
}