/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/BatchRenderer2D.hpp"
#include "Graphics/StaticSprite.hpp"
#include "Graphics/SimpleRenderer2D.hpp"

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
	Sprite sprite(0.f, 0.f, 200.f, 200.f, Vec4(0.0f, 0.0f, 1.0f, 1.0f));

	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}

		window.handleEvents();
		window.clear();

		shader.bind();

		renderer.begin();
		renderer.submit(&sprite);
		renderer.end();
		renderer.flush();

		window.swapBuffers();
	}

	return 0;
}