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

class Sandbox : public Application {
private:
	std::unique_ptr<Shader> basicShader;
	float m_Vertices[12] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	float m_Colors[16] = {
		1.0f, 0.0f,  0.0f, 1.0f,  // top right
		0.0f, 1.0f,  0.0f, 1.0f,  // bottom right
		0.0f, 0.0f,  1.0f, 1.0f,  // bottom left
		0.5f, 0.25f, 0.5f, 1.0f,  // top left 
	};
	uint32_t m_Indices[6] = {
		0, 1, 3,
		1, 2, 3,
	};
	VertexArray m_Vao;
	IndexBuffer m_Ibo;
	VertexBuffer m_Vbo, m_Cbo;
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true), m_Ibo(6) {

		setTargetFPS(120);
		setTargetUPS(120);
		setExitKey(KeyCode::Escape);

		basicShader = std::make_unique<Shader>("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");
		
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		m_Vao.bind();

		// position attribute
		m_Vbo.bind();
		m_Vao.setVertexData(0, 3, 12, m_Vertices);
		/*glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);*/
		m_Vbo.unbind();

		// color attribute
		m_Cbo.bind();
		m_Vao.setVertexData(1, 4, 16, m_Colors);
		/*glBufferData(GL_ARRAY_BUFFER, sizeof(m_Colors), m_Colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);*/
		m_Cbo.unbind();

		m_Ibo.bind();
		m_Vao.setIndexData(6, m_Indices);
		/*glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);*/
		m_Ibo.unbind();

		m_Vao.unbind();

	}

	~Sandbox() {

	}

	void update() override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()));
		
	}

	void render() override {
		basicShader->bind();
		m_Vao.bind();
		m_Ibo.bind();
		glDrawElements(GL_TRIANGLES, m_Ibo.getIndexCount(), GL_UNSIGNED_INT, 0);
		m_Vao.unbind();
		basicShader->unbind();
	}

};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}