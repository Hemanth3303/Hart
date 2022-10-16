/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"
#include "Core/Input.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/buffers/Buffer.hpp"
#include "Graphics/buffers/IndexBuffer.hpp"

#include "Maths/Maths.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;

	Window window(800, 500, "Hart Sandbox", false);
	Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	Mat4 ortho = Mat4::orthographic((float)-window.getWidth(), (float)window.getWidth(), (float)-window.getHeight(), (float)window.getHeight(), -1.0f, 1.0f);
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

	uint32_t VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	Buffer vbo(vertices, 12, 3);
	IndexBuffer ibo(indices, 6);
	vbo.bind();
	ibo.bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		std::cout << "Mouse x: " << Mouse::getMousePosition().x << "\tMouse y: " << Mouse::getMousePosition().y << "\n";
	}

	return 0;
}