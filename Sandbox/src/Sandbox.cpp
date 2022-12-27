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
		
		Vec3 a(5, 5, 9);
		Vec3 b(2, 6, 4);

		Vec3 c = Vec3::crossProduct(a, b);

		HART_CLIENT_INFO(a);
		HART_CLIENT_INFO(b);
		HART_CLIENT_INFO(c);
		HART_CLIENT_INFO(Vec3::getAngleDBetween(a.normalize(), b.normalize()));

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