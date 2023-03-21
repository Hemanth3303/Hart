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
	std::array<float, 36> m_Vertices = {
		 //position              // color                   // texture coords
		 100.0f,  100.f, 0.0f,   1.0f, 0.0f,  0.0f, 1.0f,   1.0f, 1.0f, // top right
		 100.0f, -100.f, 0.0f,   0.0f, 1.0f,  0.0f, 1.0f,   1.0f, 0.0f, // bottom right
		-100.0f, -100.f, 0.0f,   0.0f, 0.0f,  1.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-100.0f,  100.f, 0.0f,   0.5f, 0.25f, 0.5f, 1.0f,   0.0f, 1.0f, // top left 
	};
	std::array<uint32_t, 6> m_Indices = {
		0, 1, 3,
		1, 2, 3,
	};
	std::unique_ptr<Shader> shader1, shader2;
	uint32_t vao;
	IndexBuffer *m_IndexBuffer;
	VertexBuffer* m_VertexBuffer;
	Texture2D* tex;
	float angle = 0.0f;
	//to make (0,0) at center of game window
	Mat4 m_Projection = Mat4::orthographic(-(960/2.0f), (960/2.0f), -(540/2.0f), (540/2.0f), -1.0f, 1.0f);
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(144);
		setTargetUPS(144);
		setExitKey(KeyCode::Escape);

		shader1 = std::make_unique<Shader>("res/shaders/texWithColVert.glsl", "res/shaders/texWithColFrag.glsl");
		shader2 = std::make_unique<Shader>("res/shaders/texWithColVert.glsl", "res/shaders/texWithColFrag.glsl");

		BufferLayout layout = {
			{ ShaderDataType::Float3,  "aPosition" },
			{ ShaderDataType::Float4,  "aColor" },
			{ ShaderDataType::Float2,  "aTexCoord" },
		};
		
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		m_VertexBuffer = new VertexBuffer(m_Vertices.data(), sizeof(m_Vertices));
		m_VertexBuffer->bind();
		m_VertexBuffer->setLayout(layout);

		uint32_t index = 0;
		for (const auto& element : m_VertexBuffer->getLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.getComponentCount(), 
				element.getOpenGLType(), 
				element.normalized ? GL_TRUE : GL_FALSE, 
				m_VertexBuffer->getLayout().getStride(),
				reinterpret_cast<const void*>(element.offset)
			);
			index++;
		}

		m_IndexBuffer = new IndexBuffer(m_Indices.data(), 6);
		m_IndexBuffer->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices.data(), GL_STATIC_DRAW);
		m_IndexBuffer->unbind();

		shader1->bind();
		shader1->setUniform("projection", m_Projection);
		shader1->unbind();

		shader2->bind();
		shader2->setUniform("projection", m_Projection);
		shader2->unbind();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		tex = new Texture2D("res/images/awesomeface.png");

		glBindVertexArray(0);
	}

	~Sandbox() {
		delete tex;
		delete m_VertexBuffer;
		delete m_IndexBuffer;
	}

	void update(double deltaTime) override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()));
		angle += (float)deltaTime;
		if (angle >= 360.0f) {
			angle = 0.0f;
		}
	}

	void render() override {
		shader1->bind();
		glBindVertexArray(vao);
		m_IndexBuffer->bind();
		tex->bind();

		shader1->setUniform("model", Mat4::translate(Vec3(-200, 0, 0)));
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->getIndexCount(), GL_UNSIGNED_INT, 0);

		tex->unbind();
		m_IndexBuffer->unbind();
		glBindVertexArray(0);
		shader1->unbind();


		shader2->bind();
		glBindVertexArray(vao);
		m_IndexBuffer->bind();
		tex->bind();

		Mat4 model = Mat4::indentity();
		model *= Mat4::translate(Vec3(200, 0, 0)) * Mat4::rotate(angle, Vec3(0, 0, 1));
		shader2->setUniform("model", model);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->getIndexCount(), GL_UNSIGNED_INT, 0);

		tex->unbind();
		m_IndexBuffer->unbind();
		glBindVertexArray(0);
		shader2->unbind();
	}
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}