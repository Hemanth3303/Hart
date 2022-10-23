/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/BatchRenderer2D.hpp"
#include "Graphics/Layer.hpp"

#include "Maths/Maths.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Loggable.hpp"

#include "SandboxLayer.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;
	using namespace Hart::Utils;

	Window window(960, 540, "Hart Engine: Sandbox", false);
	std::shared_ptr<Shader> shader1 = std::make_shared<Shader>();
	std::shared_ptr<Shader> shader2 = std::make_shared<Shader>();

	Mat4 ortho = Mat4::orthographic((float)-window.getWidth(), (float)window.getWidth(), (float)-window.getHeight(), (float)window.getHeight(), -1.0f, 1.0f);

	shader1->bind();
	shader1->setUniform("pr_matrix", ortho);
	shader1->unbind();

	shader2->bind();
	shader2->setUniform("pr_matrix", ortho);
	shader2->unbind();

	window.enableVsync();

	SandboxLayer layer1(shader1, ortho);
	SandboxLayer layer2(shader2, ortho);

	layer1.add(std::make_shared<Sprite>(100.f, 100.f, 200.f, 200.f, Vec4(1.f, 0.f, 0.f, 1.f)));
	layer1.add(std::make_shared<Sprite>(-400.f, -300.f, 100.f, 400.f, Vec4(0.f, 1.f, 0.f, 1.f)));
	layer1.add(std::make_shared<Sprite>(100.f, -500.f, 200.f, 200.f, Vec4(0.f, 0.f, 1.f, 1.f)));

	layer2.add(std::make_shared<Sprite>(640.f, -100.f, 300.f, 200.f, Vec4(0.f, 1.f, 1.f, 1.f)));
	layer2.add(std::make_shared<Sprite>(-300.f, -30.f, 100.f, 300.f, Vec4(1.f, 1.f, 0.f, 1.f)));
	layer2.add(std::make_shared<Sprite>(100.f, -400.f, 400.f, 250.f, Vec4(1.f, 0.f, 1.f, 1.f)));

	Random rd;
	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}

		window.handleEvents();
		window.clear();

		static int x = 0, y = 0;
		x--, y++;

		shader1->bind();
		shader1->setUniform("ml_matrix", Mat4::rotate(x, Vec3(0.f, 0.f, 1.0f)) * Mat4::translate(Vec3(500, 300, 0)));
		layer1.render();
		shader1->unbind();

		shader2->bind();
		shader2->setUniform("ml_matrix", Mat4::rotate(y, Vec3(0.f, 0.f, 1.0f)) * Mat4::translate(Vec3(-300, 50, 0)));
		layer2.render();

		window.swapBuffers();
	}

	return 0;
}