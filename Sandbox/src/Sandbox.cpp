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
		
		Vec3 x(1, 2, -4);
		Vec3 y(2, -6, 2);
		Vec3 z(-3, 4, 7);

		x += y;

		z -= y;

		y += y;

		HART_CLIENT_INFO(x);
		HART_CLIENT_INFO(y);
		HART_CLIENT_INFO(z);


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