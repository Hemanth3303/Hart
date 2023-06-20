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
	std::array<float, 42> m_Vertices = {
		 //position              // color                 //texture coords
		 100.0f,  100.f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
		 100.0f, -100.f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
		-100.0f, -100.f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		-100.0f,  100.f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	};
	std::array<std::uint32_t, 6> m_Indices = {
		0, 1, 3,
		1, 2, 3,
	};
	ShaderLibrary m_ShaderLibrary;
	std::shared_ptr<VertexArray> m_VertexArray;
	OrthographicCamera m_Camera;

	Vec3 m_CameraPos = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotD = 0.0f;
	std::shared_ptr<Texture2D> m_Tex1, m_Tex2;
public:
	Sandbox()
		: Application(960, 540, "Hart Engine: Sandbox", true) , m_Camera(-(960 / 2.0f), (960 / 2.0f), -(540 / 2.0f), (540 / 2.0f)) {
		setMaxFPS(144);
		//enableVsync();
		setExitKey(KeyCode::Escape);

		m_ShaderLibrary.loadShader("textureShader", "res/shaders/textureVert.glsl", "res/shaders/textureFrag.glsl");
		m_Tex1 = std::make_shared<Texture2D>("res/images/grass_block.png", MagFilter::Nearest);
		m_Tex2 = std::make_shared<Texture2D>("res/images/awesomeface.png", MagFilter::Linear);

		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPosition" },
			{ ShaderDataType::Float4, "aColor" },
			{ ShaderDataType::Float2, "aTexCoord" }
		};

		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->bind();

		std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(m_Vertices.data(), (std::uint32_t)sizeof(m_Vertices));
		vbo->setLayout(layout);
		m_VertexArray->addVertexBuffer(vbo);

		std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(m_Indices.data(), 6);
		m_VertexArray->setIndexBuffer(ibo);

		m_VertexArray->unbind();

		m_ShaderLibrary.getShader("textureShader")->bind();
		m_ShaderLibrary.getShader("textureShader")->setUniform("uTexture", m_Tex1->getSlot());
		m_ShaderLibrary.getShader("textureShader")->unbind();
	}

	~Sandbox() {

	}

	void onEvent(const Event& e) override {
		//HART_CLIENT_LOG(e);
	}

	void update(double deltaTime) override {
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(getCurrentFPS()));

		float cameraMovementSpeed = 600.0f;

		if (InputManager::IsKeyPressed(KeyCode::A)) {
			m_CameraPos.x -= cameraMovementSpeed * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::D)) {
			m_CameraPos.x += cameraMovementSpeed * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::W)) {
			m_CameraPos.y += cameraMovementSpeed * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::S)) {
			m_CameraPos.y -= cameraMovementSpeed * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::Q)) {
			m_CameraRotD += 45 * (float)deltaTime;
		}
		if (InputManager::IsKeyPressed(KeyCode::E)) {
			m_CameraRotD -= 45 * (float)deltaTime;
		}

		m_Camera.setPosition(m_CameraPos);
		m_Camera.setRotation(m_CameraRotD);
	}

	void render() override {

		Mat4 scale = Mat4::scale(Vec3(0.15f));

		Renderer3D::BeginScene(m_Camera);
		m_Tex1->bind();
		Renderer3D::Submit(m_VertexArray, m_ShaderLibrary.getShader("textureShader"), Mat4::indentity());
		m_Tex2->bind();
		Renderer3D::Submit(m_VertexArray, m_ShaderLibrary.getShader("textureShader"), Mat4::translate(Vec3(100, 0, 1)));
		Renderer3D::EndScene();

	}
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}