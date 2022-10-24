/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/BatchRenderer2D.hpp"
#include "Graphics/Layer.hpp"
#include "Graphics/Group.hpp"

#include "Maths/Maths.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Loggable.hpp"

#include "SandboxLayer.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;
	using namespace Hart::Utils;

	Window window(960, 540, "Hart Engine: Sandbox", true);
	std::shared_ptr<Shader> shader1 = std::make_shared<Shader>();

	Mat4 ortho = Mat4::orthographic((float)-window.getWidth(), (float)window.getWidth(), (float)-window.getHeight(), (float)window.getHeight(), -1.0f, 1.0f);

	window.enableVsync();

	SandboxLayer layer1(shader1, ortho);

	std::shared_ptr<Group> group = std::make_shared<Group>(Mat4::translate(Vec3(100, 0, 0)));
	group->add(std::make_shared<Sprite>(0.f, 0.f, 100.f, 100.f, Color(1.f, 1.f, 1.f, 1.f)));

	std::shared_ptr<Group> button = std::make_shared<Group>(Mat4::translate(Vec3(-10.f, -100.f, 0)));
	button->add(std::make_shared<Sprite>(0.f, 0.f, 200.f, 200.f, Color(1.f, 0.f, 1.f, 1.f)));
	button->add(std::make_shared<Sprite>(0.5f, 0.5f, 300.f, 300.0f, Color(0.2f, 0.3f, 0.8f, 1.0)));

	group->add(button);

	layer1.add(group);

	Random rd;
	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}

		window.handleEvents();
		window.clear();

		layer1.render();

		window.swapBuffers();
	}

	return 0;
}