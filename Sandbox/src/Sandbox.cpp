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
		 100.f,  100.f, 0.0f,  // top right
		 100.f, -100.f, 0.0f,  // bottom right
		-100.f, -100.f, 0.0f,  // bottom left
		-100.f,  100.f, 0.0f   // top left 
	};
	std::array<float, 16> m_Colors = {
		1.0f, 0.0f,  0.0f, 1.0f,  // top right
		0.0f, 1.0f,  0.0f, 1.0f,  // bottom right
		0.0f, 0.0f,  1.0f, 1.0f,  // bottom left
		0.5f, 0.25f, 0.5f, 1.0f,  // top left 
	};
	std::array<float, 8> m_Textures = {
		1.0f, 1.0f,  // top right
		1.0f, 0.0f,	 // bottom right
		0.0f, 0.0f,	 // bottom left
		0.0f, 1.0f,	 // top left 
	};
	std::array<uint32_t, 6> m_Indices = {
		0, 1, 3,
		1, 2, 3,
	};
	VertexArray m_Vao;
	IndexBuffer m_Ibo;
	VertexBuffer m_Vbo, m_Cbo, m_Tbo;
	Texture2D m_Tex1;
	Texture2D m_Tex2;

	//to make (0,0) at center of game window
	Mat4 m_Projection = Mat4::orthographic(-(960/2.0f), (960/2.0f), -(540/2.0f), (540/2.0f), -1.0f, 1.0f);
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true), m_Ibo(6), m_Tex1("res/images/grass_block.png", GL_NEAREST, GL_NEAREST_MIPMAP_NEAREST), m_Tex2("res/images/awesomeface.png") {

		setTargetFPS(120);
		setTargetUPS(120);
		setExitKey(KeyCode::Escape);

		shader1 = std::make_unique<Shader>("res/shaders/textureVert.glsl", "res/shaders/textureFrag.glsl");
		
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		m_Vao.bind();

		// position attribute
		m_Vbo.bind();
		m_Vao.setVertexData(0, sizeof(m_Vertices), 3, m_Vertices.data(), 3 * sizeof(float));
		m_Vbo.unbind();

		// color attribute
		m_Cbo.bind();
		m_Vao.setVertexData(1, sizeof(m_Colors), 4, m_Colors.data(), 4 * sizeof(float));
		m_Cbo.unbind();

		//texture attribute
		m_Tbo.bind();
		m_Vao.setVertexData(2, sizeof(m_Textures), 2, m_Textures.data(), 2 * sizeof(float));
		m_Tbo.unbind();

		m_Ibo.bind();
		m_Vao.setIndexData((uint32_t)m_Indices.size(), m_Indices.data());
		m_Ibo.unbind();

		m_Vao.unbind();

		shader1->bind();
		shader1->setUniform("projection", m_Projection);
		shader1->setUniform("gameTexture1", 0);
		shader1->setUniform("gameTexture2", 1);
		shader1->unbind();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	}

	~Sandbox() {

	}

	void update() override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()));
		
	}

	void render() override {
		shader1->bind();
		m_Tex1.bind();
		m_Tex2.bind();
		m_Vao.bind();
		m_Ibo.bind();
		glDrawElements(GL_TRIANGLES, m_Ibo.getIndexCount(), GL_UNSIGNED_INT, 0);

		m_Tex1.unbind();
		m_Tex2.unbind();
		m_Ibo.unbind();
		m_Vao.unbind();
		shader1->unbind();
	}

};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}