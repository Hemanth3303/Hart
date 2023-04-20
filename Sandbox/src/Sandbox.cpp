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
	std::unique_ptr<Shader> shader1, shader2, shader3;
	std::shared_ptr<VertexArray> m_VertexArray;
	Texture2D* tex;
	float angle = 0.0f;
	Mat4 m_View = Mat4::indentity();
	//to make (0,0) at center of game window
	Mat4 m_Projection = Mat4::orthographic(-(960/2.0f), (960/2.0f), -(540/2.0f), (540/2.0f), -1.0f, 1.0f);
	Vec3 m_TinyGayPogSmileyPosition;
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(144);
		setTargetUPS(144);
		setExitKey(KeyCode::Escape);

		shader1 = std::make_unique<Shader>("res/shaders/texWithColVert.glsl", "res/shaders/texWithColFrag.glsl");
		shader2 = std::make_unique<Shader>("res/shaders/texWithColVert.glsl", "res/shaders/texWithColFrag.glsl");
		shader3 = std::make_unique<Shader>("res/shaders/texWithColVert.glsl", "res/shaders/texWithColFrag.glsl");

		BufferLayout layout = {
			{ ShaderDataType::Float3,  "aPosition" },
			{ ShaderDataType::Float4,  "aColor" },
			{ ShaderDataType::Float2,  "aTexCoord" },
		};
		
		m_VertexArray=std::make_shared<VertexArray>();
		m_VertexArray->bind();

		std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(m_Vertices.data(), (uint32_t)sizeof(m_Vertices));
		vbo->setLayout(layout);
		m_VertexArray->addVertexBuffer(vbo);

		std::shared_ptr <IndexBuffer> ibo = std::make_shared<IndexBuffer>(m_Indices.data(), 6);
		m_VertexArray->setIndexBuffer(ibo);

		m_VertexArray->unbind();

		shader1->bind();
		shader1->setUniform("uProjectionMatrix", m_Projection);
		shader1->unbind();

		shader2->bind();
		shader2->setUniform("uProjectionMatrix", m_Projection);
		shader2->unbind();

		shader3->bind();
		shader3->setUniform("uProjectionMatrix", m_Projection);
		shader3->unbind();

		tex = new Texture2D("res/images/awesomeface.png");

		uint32_t buff[32 * 32];
		Image x(buff, 32, 32);
	}

	~Sandbox() {
		delete tex;
	}

	void update(double deltaTime) override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()) + " | DeltaTime: "+ std::to_string(deltaTime));

		angle += (float)deltaTime;
		if (angle >= 360.0f) {
			angle = 0.0f;
		}

		m_TinyGayPogSmileyPosition.x = (float)(cosD(-angle) * 400);
		m_TinyGayPogSmileyPosition.y = (float)(sinD(-angle) * 400);

	}

	void render() override {

		{
			shader3->bind();
			tex->bind();

			Mat4 model = Mat4::indentity();
			model *= Mat4::scale(Vec3(0.2f, 0.2f, 0.0f));
			model *= Mat4::translate(m_TinyGayPogSmileyPosition);
			model *= Mat4::rotate(-3 * angle, Vec3(0, 0, 1));
			shader2->setUniform("uModelMatrix", model);
			shader3->setUniform("uViewMatrix", m_View);

			Renderer2D::BeginScene();
			Renderer2D::Submit(m_VertexArray);
			Renderer2D::EndScene();

			tex->unbind();
			shader3->unbind();
		}

		{
			shader1->bind();
			tex->bind();


			shader1->setUniform("uModelMatrix", Mat4::translate(Vec3(-200, 0, 0)));
			shader2->setUniform("uViewMatrix", m_View);

			Renderer2D::BeginScene();
			Renderer2D::Submit(m_VertexArray);
			Renderer2D::EndScene();

			tex->unbind();
			shader1->unbind();
		}

		{
			shader2->bind();
			tex->bind();

			Mat4 model = Mat4::indentity();
			model *= Mat4::translate(Vec3(200, 0, 0)) * Mat4::rotate(angle, Vec3(0, 0, 1));
			shader2->setUniform("uModelMatrix", model);
			shader2->setUniform("uViewMatrix", m_View);
			
			Renderer2D::BeginScene();
			Renderer2D::Submit(m_VertexArray);
			Renderer2D::EndScene();

			tex->unbind();
			shader2->unbind();
		}

	}
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}