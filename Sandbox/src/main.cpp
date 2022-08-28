/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/HartApplication.hpp"

class Sandbox : public Hart::Core::HartApplication {
protected:
	void init() {
		HART_CLIENT_INFO("init");
	}
	void update() {
		HART_CLIENT_INFO("update");
	}
	void render() {
		HART_CLIENT_INFO("render");
	}
	void deinit() {
		HART_CLIENT_INFO("deinit");
	}
};

#include <iostream>

int main() {

	Sandbox sandbox;

	sandbox.start();
	sandbox.run();
	sandbox.shutdown();

	std::cin.get();
	return 0;
}