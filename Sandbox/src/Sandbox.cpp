/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

using namespace Hart;
using namespace Hart::Graphics;
using namespace Hart::Maths;
using namespace Hart::Events;
using namespace Hart::Inputs;
using namespace Hart::Utils;

// shader test code from https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/3.3.shaders_class/shaders_class.cpp

class Sandbox : public Application {
private:
	std::unique_ptr<Shader> basicShader;
	float m_Vertices[6 * 3] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};
	uint32_t  m_Vbo, m_Vao;
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(120);
		setTargetUPS(120);

		basicShader = std::make_unique<Shader>("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");
		
		glGenVertexArrays(1, &m_Vao);
		glGenBuffers(1, &m_Vbo);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(m_Vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

	}

	~Sandbox() {
		glDeleteBuffers(1, &m_Vbo);
		glDeleteVertexArrays(1, &m_Vao);
	}

	void update() override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()));
		
	}

	void render() override {
		basicShader->bind();
		glBindVertexArray(m_Vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		basicShader->unbind();
	}

};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}