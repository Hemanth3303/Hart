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

		if (Hart::Mouse::isButtonPressed(Hart::Mouse::Button::ButtonLeft)) {
			HART_CLIENT_INFO("left click");
		}
		else if (Hart::Mouse::isButtonPressed(Hart::Mouse::Button::ButtonRight)) {
			HART_CLIENT_INFO("right click");
		}
		else if (Hart::Mouse::isButtonPressed(Hart::Mouse::Button::ButtonMiddle)) {
			HART_CLIENT_INFO("middle click");
		}
		else if (Hart::KeyBoard::isKeyPressed(Hart::KeyBoard::Key::A)) {
			HART_CLIENT_INFO("Key 'A'");
		}
		else {
			HART_CLIENT_INFO("not clicked");
		}

		app.render();
	}
	
	return 0;
}