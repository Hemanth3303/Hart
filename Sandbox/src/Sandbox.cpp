/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

class Sandbox : public Hart::Application {
public:
	Sandbox() {
		using namespace Hart;
		using namespace Hart::Utils;

		Random rd;
		std::cout << rd.getRandomInt32(0, 100) << "\n";
		std::cout << rd.getRandomInt64(-20, 50) << "\n";
		std::cout << rd.getRandomFloat(-200.54f, 300.25f) << "\n";
		std::cout << rd.getRandomDouble(-500.065, 546.615) << "\n";
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