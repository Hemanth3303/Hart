/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

using namespace Hart;
using namespace Hart::Utils;

class Sandbox : public Hart::Application {
public:
	Sandbox() {
		std::cout << FileManager::ReadFromFile("./src/Sandbox.cpp");
		FileManager::WriteToFile("TESTING", "TEST_LOG.txt", "./logs");
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