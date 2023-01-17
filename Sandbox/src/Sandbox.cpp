/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

using namespace Hart;
using namespace Hart::Maths;
using namespace Hart::Utils;

class Sandbox : public Application {
public:
	Sandbox() {
		setWindowConfigs(960, 540, "Hart Engine: Sandbox", true);
		setExitKey(Keyboard::Key::Escape);
		


	}

	~Sandbox() {

	}

	void update() override {

	}

	void render() override {

	}
};

Hart::Application* Hart::CreateApplication() {
	return new Sandbox();
}