/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/StaticSprite.hpp"
#include "Graphics/SimpleRenderer2D.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/BatchRenderer2D.hpp"

#include "Maths/Maths.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Loggable.hpp"

#define BATCHRENDERER 1

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;
	using namespace Hart::Utils;

	Window window(1000, 800, "Hart Engine: Sandbox", true);
	Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	Mat4 ortho = Mat4::orthographic((float)-window.getWidth(), (float)window.getWidth(), (float)-window.getHeight(), (float)window.getHeight(), -1.0f, 1.0f);

	shader.bind();
	shader.setUniform("pr_matrix", ortho);
	shader.unbind();

	window.enableVsync();

	BatchRenderer2D renderer;

	std::vector<Renderable2D*> sprites;

	Random rd;

#if BATCHRENDERER 
	for (float y = (float)-window.getHeight(); y < (float)window.getHeight(); y += 10) {
		for (float x = (float)-window.getWidth(); x < (float)window.getWidth(); x += 10) {
			sprites.push_back(new Sprite(x * 5, y * 5, 20, 20, Maths::Vec4(rd.getFloat(0.0f, 1.0f), rd.getFloat(0.0f, 1.0f), rd.getFloat(0.0f, 1.0f), 1.0f)));
	}
}
#else
	for (float y = (float)-window.getHeight(); y < (float)window.getHeight(); y += 10) {
		for (float x = (float)-window.getWidth(); x < (float)window.getWidth(); x += 10) {
			sprites.push_back(new StaticSprite(x * 5, y * 5, 20, 20, Maths::Vec4(rd.getFloat(0.0f, 1.0f), rd.getFloat(0.0f, 1.0f), rd.getFloat(0.0f, 1.0f), 1.0f), shader));
		}
	}
#endif



	std::string info;

	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();
		//std::cout << "FPS: " << timer.getFPS() << "\n";

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}
		info = "Number of sprites being drawn on screen currently: ";
		info += std::to_string(sprites.size());

		HART_CLIENT_INFO(info);

		window.handleEvents();
		window.clear();

		shader.bind();

		renderer.begin();
		for (const auto& sprite : sprites) {
			renderer.submit(sprite);
		}
		renderer.end();
		renderer.flush();

		window.swapBuffers();
	}


	for (const auto& sprite : sprites) {
		delete sprite;
	}

	return 0;
}