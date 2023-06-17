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
	std::shared_ptr<Shader> shader1;
	std::shared_ptr<VertexArray> m_VertexArray;
	OrthographicCamera m_Camera;

	Vec3 m_CameraPos = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotD = 0.0f;
	//to make (0,0) at center of game window
public:
	Sandbox()
		: Application(960, 540, "Hart Engine: Sandbox", true) , m_Camera(-(960 / 2.0f), (960 / 2.0f), -(540 / 2.0f), (540 / 2.0f)) {

		setTargetFPS(500);
		setTargetUPS(500);
		setExitKey(KeyCode::Escape);

		shader1 = std::make_shared<Shader>("res/shaders/cameraVert.glsl", "res/shaders/cameraFrag.glsl");

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
		shader1->setUniform("uViewProjectionMatrix", m_Camera.getViewProjectionMatrix());
		shader1->unbind();
		
	}

	~Sandbox() {

	}

	void update(double deltaTime) override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()) + " | DeltaTime: "+ std::to_string(deltaTime));
		if (InputManager::IsKeyPressed(KeyCode::A)) {
			m_CameraPos.x -= 5.0f * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::D)) {
			m_CameraPos.x += 5.0f * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::W)) {
			m_CameraPos.y += 5.0f * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::S)) {
			m_CameraPos.y -= 5.0f * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::ArrowLeft)) {
			m_CameraRotD -= 0.5f * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::ArrowRight)) {
			m_CameraRotD += 0.5f * (float)deltaTime;
		}

		m_Camera.setPosition(m_CameraPos);
		m_Camera.setRotation(m_CameraRotD);
	}

	void render() override {

		{
			Renderer2D::BeginScene(m_Camera);
			Renderer2D::Submit(m_VertexArray, shader1);
			Renderer2D::EndScene();
		}

	}
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}