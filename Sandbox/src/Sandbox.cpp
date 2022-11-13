/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

class Sandbox : public Hart::Application {
public:
	Sandbox() {
		using namespace Hart;
		using namespace Hart::Utils;
		using namespace Hart::Maths;

		HART_CLIENT_INFO(E);
		HART_CLIENT_INFO(PI);

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