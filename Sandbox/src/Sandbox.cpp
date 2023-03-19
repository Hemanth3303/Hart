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
	std::unique_ptr<Shader> shader1;
	std::array<float, 12> m_Vertices = {
		 100.0f,  100.f, 0.0f,  // top right
		 100.0f, -100.f, 0.0f,  // bottom right
		-100.0f, -100.f, 0.0f,  // bottom left
		-100.0f,  100.f, 0.0f   // top left 
	};
	std::array<float, 16> m_Colors = {
		1.0f, 0.0f,  0.0f, 1.0f,  // top right
		0.0f, 1.0f,  0.0f, 1.0f,  // bottom right
		0.0f, 0.0f,  1.0f, 1.0f,  // bottom left
		0.5f, 0.25f, 0.5f, 1.0f,  // top left 
	};
	std::array<float, 8> m_TexCoords = {
		1.0f, 1.0f,  // top right
		1.0f, 0.0f,	 // bottom right
		0.0f, 0.0f,	 // bottom left
		0.0f, 1.0f,	 // top left 
	};
	std::array<uint32_t, 6> m_Indices = {
		0, 1, 3,
		1, 2, 3,
	};
	uint32_t vao;
	IndexBuffer *m_Ibo;
	VertexBuffer *m_Vbo, *m_Cbo, *m_Tbo;
	Texture2D* tex;
	//to make (0,0) at center of game window
	Mat4 m_Projection = Mat4::orthographic(-(960/2.0f), (960/2.0f), -(540/2.0f), (540/2.0f), -1.0f, 1.0f);
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(144);
		setTargetUPS(144);
		setExitKey(KeyCode::Escape);

		shader1 = std::make_unique<Shader>("res/shaders/texWithColVert.glsl", "res/shaders/texWithColFrag.glsl");
		
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);
		// position attribute
		m_Vbo = new VertexBuffer(m_Vertices.data(), sizeof(m_Vertices));
		m_Vbo->bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		// color attribute
		m_Cbo = new VertexBuffer(m_Colors.data(), sizeof(m_Colors));
		m_Cbo->bind();
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

		//texture attribute
		m_Tbo = new VertexBuffer(m_TexCoords.data(), sizeof(m_TexCoords));
		m_Tbo->bind();
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		m_Ibo = new IndexBuffer(m_Indices.data(), 6);

		m_Ibo->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices.data(), GL_STATIC_DRAW);
		m_Ibo->unbind();

		shader1->bind();
		shader1->setUniform("projection", m_Projection);
		shader1->unbind();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		tex = new Texture2D("res/images/awesomeface.png");

		glBindVertexArray(0);
	}

	~Sandbox() {
		delete tex;
	}

	void update() override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()));
	}

	void render() override {
		shader1->bind();
		glBindVertexArray(vao);
		m_Ibo->bind();
		tex->bind();

		glDrawElements(GL_TRIANGLES, m_Ibo->getIndexCount(), GL_UNSIGNED_INT, 0);

		tex->unbind();
		m_Ibo->unbind();
		glBindVertexArray(0);
		shader1->unbind();
	}
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}