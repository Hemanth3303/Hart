/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

using namespace Hart;
using namespace Hart::Utils;

class Sandbox : public Hart::Application {
public:
	Sandbox() {
		Logger::LogMessage('e', LogSeverity::INFO);
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