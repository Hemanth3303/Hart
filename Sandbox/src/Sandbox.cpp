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
	uint32_t m_Indices[6] = {
		0, 1, 3,
		1, 2, 3,
	};
	VertexArray m_Vao;
	IndexBuffer m_Ibo;
	VertexBuffer m_Vbo, m_Cbo;

	//to make (0,0) at center of game window
	Mat4 m_Projection = Mat4::orthographic(-(960/2.0f), (960/2.0f), -(540/2.0f), (540/2.0f), -1.0f, 1.0f);
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
		m_Vao.setVertexData(0, sizeof(m_Vertices), 3, m_Vertices.data());
		m_Vbo.unbind();

		// color attribute
		m_Cbo.bind();
		m_Vao.setVertexData(1, sizeof(m_Colors), 4, m_Colors.data());
		m_Cbo.unbind();

		m_Ibo.bind();
		m_Vao.setIndexData(6, m_Indices);
		m_Ibo.unbind();

		m_Vao.unbind();

		Mat4 model = Mat4(1.0f);
		model = Mat4::translate(Vec3(100, -50, 0)) * Mat4::rotate(45.0f, Vec3(0, 0, 1)) * Mat4::scale(Vec3(1.25, 0.5, 1));
		basicShader->bind();
		basicShader->setUniform("projection", m_Projection);
		basicShader->setUniform("model", model);
		basicShader->unbind();

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