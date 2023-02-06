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
		HART_CLIENT_LOG(InputManager::GetMousePosition());
		if (InputManager::IsMouseButtonPressed(MouseCode::Left)) {
			InputManager::SetMousePosition(Vec2(getWindowWidth() / 2, getWindowHeight() / 2));
		}
	}

	void render() override {
		
	}
};

Hart::Application* Hart::CreateApplication() {
	return new Sandbox();
}