/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"

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

	shader.bind();
	shader.setUniform("pr_matrix", ortho);
	shader.unbind();

	Random rd;
	Timer timer;

	float vertices[] = {
		 200.0f,  200.0f, 0.0f,  // top right
		 200.0f, -200.0f, 0.0f,  // bottom right
		-200.0f, -200.0f, 0.0f,  // bottom left
		-200.0f,  200.0f, 0.0f   // top left 
	};
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	uint32_t vao, vbo, ibo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		timer.update();

		if (KeyBoard::isKeyPressed(KeyBoard::Key::Escape)) {
			glfwSetWindowShouldClose(window.getGlfwWindow(), true);
		}

		window.handleEvents();
		window.clear();
		//begin draw calls
		
		shader.bind();
		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//end draw calls
		window.swapBuffers();
	}

	return 0;
}