/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

class Sandbox : public Hart::Application {
public:
	Sandbox() {

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