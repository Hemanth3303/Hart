/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Window.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/buffers/Buffer.hpp"
#include "Graphics/buffers/IndexBuffer.hpp"
#include "Graphics/buffers/VertexArray.hpp"

#include "Maths/Mat4.hpp"

int main(int argc, char** argv) {

	using namespace Hart;
	using namespace Hart::Graphics;
	using namespace Hart::Maths;

	Window window(640, 480, "HART ENGINE: SANDBOX", false);
	Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	float vertices[] = {
	     0.5f,  0.5f, 0.0f,  // top right
	     0.5f, -0.5f, 0.0f,  // bottom right
	    -0.5f, -0.5f, 0.0f,  // bottom left
	    -0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	VertexArray vao;
	vao.addBuffer(new Buffer(vertices, 12, 3), 0);
	vao.bind();
	IndexBuffer ibo(indices, 6);
	ibo.bind();
	vao.unbind();

	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		window.handleEvents();
		window.update();

		window.clear();
		//draw calls

		shader.bind();
		vao.bind();
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);

		window.swapBuffers();
	}
	
	return 0;
}