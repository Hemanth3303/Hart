/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

class Sandbox : public Hart::Application {
public:
	Sandbox() {
		using namespace Hart;
		using namespace Hart::Maths;
		using namespace Hart::Utils;
		
		Vec4 a(9, 0, 9, 0);
		Vec4 b(0, 9, 3, 6);

		HART_CLIENT_INFO(a);
		HART_CLIENT_INFO(b);
		HART_CLIENT_INFO(Vec4::getAngleDBetween(a.normalize(), b.normalize()));

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