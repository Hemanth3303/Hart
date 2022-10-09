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
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	VertexArray vao;
	vao.addBuffer(new Buffer(vertices, 9, 3), 0);

	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		window.handleEvents();
		window.update();

		window.clear();
		//draw calls

		shader.bind();
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.swapBuffers();
	}
	
	return 0;
}