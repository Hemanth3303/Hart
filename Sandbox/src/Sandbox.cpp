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
		 //position              // color                
		 100.0f,  100.f, 0.0f,   1.0f, 0.0f,  0.0f, 1.0f,
		 100.0f, -100.f, 0.0f,   0.0f, 1.0f,  0.0f, 1.0f,
		-100.0f, -100.f, 0.0f,   0.0f, 0.0f,  1.0f, 1.0f,
		-100.0f,  100.f, 0.0f,   0.5f, 0.25f, 0.5f, 1.0f,
	};
	std::array<std::uint32_t, 6> m_Indices = {
		0, 1, 3,
		1, 2, 3,
	};
	std::unique_ptr<Shader> shader1;
	std::shared_ptr<VertexArray> m_VertexArray;
	Mat4 m_View = Mat4::indentity();
	//to make (0,0) at center of game window
	Mat4 m_Projection = Mat4::orthographic(-(960/2.0f), (960/2.0f), -(540/2.0f), (540/2.0f), -1.0f, 1.0f);
public:
	Sandbox()
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(144);
		setTargetUPS(144);
		setExitKey(KeyCode::Escape);

		shader1 = std::make_unique<Shader>("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

		BufferLayout layout = {
			{ ShaderDataType::Float3,  "aPosition" },
			{ ShaderDataType::Float4,  "aColor" },
		};

		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->bind();

		std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(m_Vertices.data(), (std::uint32_t)sizeof(m_Vertices));
		vbo->setLayout(layout);
		m_VertexArray->addVertexBuffer(vbo);

		std::shared_ptr <IndexBuffer> ibo = std::make_shared<IndexBuffer>(m_Indices.data(), 6);
		m_VertexArray->setIndexBuffer(ibo);

		m_VertexArray->unbind();

		shader1->bind();
		shader1->setUniform("uProjectionMatrix", m_Projection);
		shader1->unbind();

		Mat4 mat4 = {
			7, 1, 3, 6,
			2, 3, 4, 0,
			5, 2, 2, 5,
			9, 4, 7, 1,
		};
		HART_CLIENT_LOG("Matrix");
		HART_CLIENT_LOG(mat4);
		std::cout << std::endl;
		HART_CLIENT_LOG("Determinant");
		HART_CLIENT_LOG(Mat4::determinant(mat4));
		std::cout << std::endl;
		HART_CLIENT_LOG("Adjoint");
		HART_CLIENT_LOG(Mat4::adjoint(mat4));
		std::cout << std::endl;
		HART_CLIENT_LOG("Inverse");
		HART_CLIENT_LOG(Mat4::inverse(mat4));
	}

	~Sandbox() {

	}

	void update(double deltaTime) override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()) + " | DeltaTime: "+ std::to_string(deltaTime));
	}

	void render() override {

		{
			shader1->bind();

			shader1->setUniform("uModelMatrix", Mat4::translate(Vec3(100, 100, 0)));
			shader1->setUniform("uViewMatrix", m_View);

			Renderer2D::BeginScene();
			Renderer2D::Submit(m_VertexArray);
			Renderer2D::EndScene();

			shader1->unbind();
		}

	}
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}