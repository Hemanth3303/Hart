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

	Window window(800, 500, "Hart Engine: Sandbox", true);
	Shader shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	Mat4 ortho = Mat4::orthographic((float)-window.getWidth(), (float)window.getWidth(), (float)-window.getHeight(), (float)window.getHeight(), -1.0f, 1.0f);
	Mat4 ml = Mat4::scale(Vec3(2, 2, 0));

	float vertices[] = {
	    100.0f, -100.0f, 0.0f,  // bottom right
	   -100.0f, -100.0f, 0.0f,  // bottom left
		0.0f, 100.0f, 0.0f,     // top 
	};

	float colors[] = {
	    1.0f, 0.0f, 0.0f, 1.0f,  // bottom right
		0.0f, 1.0f, 0.0f, 1.0f,	 // bottom left
		0.0f, 0.0f, 1.0f, 1.0f,	 // top 
	};

	VertexArray vao;

	vao.addBuffer(new Buffer(vertices, 9, 3), 0);
	vao.addBuffer(new Buffer(colors, 12, 4), 1);
	vao.bind();

	shader.bind();
	shader.setUniform("pr_matrix", ortho);
	shader.setUniform("ml_matrix", ml);
	shader.unbind();

	window.enableVsync();

	Timer timer;
	while (!glfwWindowShouldClose(window.getGlfwWindow())) {
		window.handleEvents();

		window.clear();

		timer.update();
		shader.bind();
		vao.bind();

		ml *= Mat4::rotate((float)timer.getDeltaTime() * -100, Vec3(0, 0, 1));
		shader.setUniform("ml_matrix", ml);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		HART_CLIENT_INFO(42);

		vao.unbind();
		shader.unbind();

		window.swapBuffers();
	}

	return 0;
}