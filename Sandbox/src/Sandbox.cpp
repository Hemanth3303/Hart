/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

using namespace Hart;
using namespace Hart::Maths;
using namespace Hart::Events;
using namespace Hart::Inputs;
using namespace Hart::Utils;

class Sandbox : public Application {
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(120);
		setTargetUPS(120);



	}

	~Sandbox() {

	}

	void update() override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()));
		switch (InputManager::GetCurrentKey()) {
			case KeyCode::Space:
				HART_CLIENT_LOG("SPACE");
				break;
			case KeyCode::A:
				HART_CLIENT_LOG("A");
				break;
			case KeyCode::D:
				HART_CLIENT_LOG("D");
				break;
			case KeyCode::W:
				HART_CLIENT_LOG("W");
				break;
			case KeyCode::S:
				HART_CLIENT_LOG("S");
				break;
			case KeyCode::Unknown:
				HART_CLIENT_WARNING("UNKNOWN KEY");
				break;
		}
		switch (InputManager::GetCurrentMouseButton()) {
			case MouseCode::Left:
				HART_CLIENT_LOG("LEFT");
				break;
			case MouseCode::Right:
				HART_CLIENT_LOG("RIGHT");
				break;
			case MouseCode::Middle:
				HART_CLIENT_LOG("MIDDLE");
				break;
			case MouseCode::Unknown:
				HART_CLIENT_WARNING("UNKNOWN BTN");
				break;
		}
	}

	void render() override {
		
	}

};

Hart::Application* Hart::CreateApplication() {
	return new Sandbox();
}