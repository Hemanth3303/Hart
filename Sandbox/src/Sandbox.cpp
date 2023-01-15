/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

class Sandbox : public Hart::Application {
public:
	Sandbox() {
		setWindowConfigs(960, 540, "Hart Engine: Sandbox", true);
		setExitKey(Hart::Keyboard::Key::Escape);
	}

	~Sandbox() {

	}

	void update() override {
		HART_CLIENT_INFO(getMousePositon());
		if (Hart::Keyboard::isKeyDown(Hart::Keyboard::Key::R)) {
			setMousePosition({ getWindowWidth() / 2.0f, getWindowHeight() / 2.0f });
		}
	}

	void render() override {

	}
};

Hart::Application* Hart::CreateApplication() {
	return new Sandbox();
}