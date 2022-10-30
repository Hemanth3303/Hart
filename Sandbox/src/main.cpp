/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/buffers/Buffer.hpp"
#include "Graphics/buffers/IndexBuffer.hpp"
#include "Graphics/buffers/VertexArray.hpp"

#include "Maths/Maths.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Loggable.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;
	using namespace Hart::Utils;

	Window window(960, 540, "Hart Engine: Sandbox", true);
	Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	Mat4 ortho = Mat4::orthographic((float)-window.getWidth(), (float)window.getWidth(), (float)-window.getHeight(), (float)window.getHeight(), -1.f, 1.f);

	shader.enable();
	shader.setUniform("pr_matrix", ortho);
	shader.disable();

	float vertices[] = {
		-200.0f, -200.0f, 0.0f,
		-200.0f,  200.0f, 0.0f,
		 200.0f,  200.0f, 0.0f,
		 200.0f, -200.0f, 0.0f
	};

	float colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f, 
		0.0f, 1.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 1.0f, 
		1.0f, 0.0f, 1.0f, 1.0f, 
	};

	unsigned int indices[] = {
		0, 1, 2,   // first triangle
		2, 3, 0    // second triangle
	};
	VertexArray vao;
	IndexBuffer ibo(indices, 6);
	vao.bind();
	ibo.bind();

	vao.addBuffer(Buffer(vertices, 12, 3), 0);
	vao.addBuffer(Buffer(colors, 16, 4), 1);

	vao.unbind();

	Random rd;
	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}

		window.handleEvents();
		window.clear();
		//begin draw calls
		
		shader.enable();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//end draw calls
		window.swapBuffers();
	}

	return 0;
}