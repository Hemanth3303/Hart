/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"

#include "Graphics/Shader.hpp"

#include "Maths/Maths.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;

	Window window(640, 480, "Hart Sandbox", true);
	Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	Mat4 ortho = Mat4::orthographic(-window.getWidth(), window.getWidth(), -window.getHeight(), window.getHeight(), -1.0f, 1.0f);
	Mat4 ml = Mat4::scale(Vec3(1, 1, 0)) * Mat4::translate(Vec3(100, 200, 0)) * Mat4::rotate(45, Vec3(0, 0, 1));

	float vertices[] = {
	    100.0f,  100.0f, 0.0f,  // top right
	    100.0f, -100.0f, 0.0f,  // bottom right
	   -100.0f, -100.0f, 0.0f,  // bottom left
	   -100.0f,  100.0f, 0.0f   // top left 
	};

	uint32_t indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	uint32_t VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	shader.bind();
	shader.setUniform("pr_matrix", ortho);
	shader.setUniform("ml_matrix", ml);

	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		window.handleEvents();

		window.clear();

		shader.bind();
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.swapBuffers();
	}

	return 0;
}