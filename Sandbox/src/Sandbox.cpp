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
		
	}

	void render() override {
		
	}

};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}