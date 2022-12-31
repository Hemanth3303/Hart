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

		Mat4 ortho = Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, 0.1f, 10.0f);
		Mat4 persp = Mat4::perspective(45, 16.0f / 9.0f, 0.1f, 10.0f);

		std::cout << "\nOrthographic projection matrix: \n" << ortho;
		std::cout << "\nPerspective projection matrix: \n" << persp;

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