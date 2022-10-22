/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/BatchRenderer2D.hpp"

#include "Maths/Maths.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Loggable.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;
	using namespace Hart::Utils;

	Window window(800, 500, "Hart Engine: Sandbox", true);
	Shader shader;

	Mat4 ortho = Mat4::orthographic((float)-window.getWidth(), (float)window.getWidth(), (float)-window.getHeight(), (float)window.getHeight(), -1.0f, 1.0f);

	shader.bind();
	shader.setUniform("pr_matrix", ortho);
	shader.unbind();

	window.enableVsync();

	BatchRenderer2D renderer;
	Sprite sprite(0, 0, 100, 100, Vec4(0.0f, 0.0f, 1.0f, 1.0f));

	Mat4 ml = Mat4::translate(sprite.getPosition());

	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}

		if (KeyBoard::isKeyPressed(KeyBoard::Key::A)) {
			ml *= Mat4::translate(Vec3(-800 * timer.getDeltaTime(), 0, 0));
		}
		if (KeyBoard::isKeyPressed(KeyBoard::Key::D)) {
			ml *= Mat4::translate(Vec3(800 * timer.getDeltaTime(), 0, 0));
		}
		if (KeyBoard::isKeyPressed(KeyBoard::Key::W)) {
			ml *= Mat4::translate(Vec3(0, 800 * timer.getDeltaTime(), 0));
		}
		if (KeyBoard::isKeyPressed(KeyBoard::Key::S)) {
			ml *= Mat4::translate(Vec3(0, -800 * timer.getDeltaTime(), 0));
		}

		window.handleEvents();
		window.clear();

		shader.bind();
		shader.setUniform("ml_matrix", ml);

		renderer.begin();
		renderer.submit(&sprite);
		renderer.end();
		renderer.flush();

		window.swapBuffers();
	}

	return 0;
}