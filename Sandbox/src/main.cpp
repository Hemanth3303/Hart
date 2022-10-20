/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/SimpleRenderer2D.hpp"
#include "Graphics/StaticSprite.hpp"

#include "Maths/Maths.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Loggable.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;
	using namespace Hart::Utils;

	Window window(800, 500, "Hart Engine: Sandbox", true);
	Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	Mat4 ortho = Mat4::orthographic((float)-window.getWidth(), (float)window.getWidth(), (float)-window.getHeight(), (float)window.getHeight(), -1.0f, 1.0f);

	shader.bind();
	shader.setUniform("pr_matrix", ortho);
	shader.unbind();

	window.enableVsync();

	StaticSprite sprite(Vec3(-100.0f, -100.0f, 0.0f), Vec2(200.0f, 200.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f), shader);
	SimpleRenderer2D renderer;

	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();
		//std::cout << "FPS: " << timer.getFPS() << "\n";

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}

		window.handleEvents();
		window.clear();

		shader.bind();
		renderer.submit(&sprite);
		renderer.flush();

		window.swapBuffers();
	}

	return 0;
}