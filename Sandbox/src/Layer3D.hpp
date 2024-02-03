#pragma once

#include "Hart.hpp"

class Layer3D : public Hart::Layer {
private:
	std::shared_ptr<Hart::VertexArray> m_Vao;
	std::shared_ptr<Hart::Shader> m_Shader;
	std::shared_ptr<Hart::PerspectiveCamera> m_Camera;
	std::shared_ptr<Hart::Texture2D> m_GrassTex;

	float angle = 0.0f;
	bool firstMouse = true;
	float lastX = 960.0f / 2.0;
	float lastY = 540.0 / 2.0;
	float fovD = 45.0f;
	float m_AspectRatio = 0.0f;

	std::vector<Hart::Vec3> cubePositions = {
		Hart::Vec3(0.0f,  0.0f,  0.0f),
		Hart::Vec3(2.0f,  3.0f, -1.0f),
		Hart::Vec3(-1.5f, -2.2f, -2.5f),
		Hart::Vec3(-3.8f, -2.0f, -12.3f),
		Hart::Vec3(2.4f, -0.4f, -3.5f),
		Hart::Vec3(-1.7f,  3.0f, -7.5f),
		Hart::Vec3(1.3f, -2.0f, -2.5f),
		Hart::Vec3(1.5f,  2.0f, -2.5f),
		Hart::Vec3(1.5f,  0.2f, -1.5f),
		Hart::Vec3(-1.3f,  1.0f, -1.5f)
	};

public:
	Layer3D(const std::string& name = "Layer3D")
		: Layer(name) {

		using namespace Hart;
		float vertices[] = {
			// Positions            // colors
			-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.75f,
			 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.75f,
			 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.75f,
			 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.75f,
			-0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.75f,
			-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.75f,
								    
			-0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.75f,
			 0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.75f,
			 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.75f,
			 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.75f,
			-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.75f,
			-0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.75f,
								    
			-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 0.75f,
			-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 0.75f,
			-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 0.75f,
			-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 0.75f,
			-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 0.75f,
			-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 0.75f,
								    
			 0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 1.0f, 0.75f,
			 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f, 0.75f,
			 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f, 0.75f,
			 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f, 0.75f,
			 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f, 0.75f,
			 0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 1.0f, 0.75f,
								    
			-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 0.75f,
			 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 0.75f,
			 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f, 0.75f,
			 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f, 0.75f,
			-0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f, 0.75f,
			-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f, 0.75f,
								    
			-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f, 0.75f,
			 0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f, 0.75f,
			 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 0.75f,
			 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 0.75f,
			-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 0.75f,
			-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f, 0.75f,
		};

		m_Vao = std::make_shared<Hart::VertexArray>();
		Hart::BufferLayout layout = {
			{ Hart::ShaderDataType::Float3, "aPosition" },
			{ Hart::ShaderDataType::Float4, "aColor" },
		};
		std::shared_ptr <Hart::VertexBuffer> vbo=std::make_shared<Hart::VertexBuffer>(vertices, (uint32_t)sizeof(vertices));
		vbo->setLayout(layout);
		m_Vao->setVertexBuffer(vbo);
		m_Shader = Hart::Application::Get()->getShader("CubeShader3D");
		m_Shader->bind();

		Hart::Texture2DSpecification pixelArtSpec;
		pixelArtSpec.magFilter = Hart::TextureMagFilter::Nearest;

		m_GrassTex = std::make_shared<Hart::Texture2D>("res/images/grass_block.png", pixelArtSpec);
		m_GrassTex->bind(0);
	}

	~Layer3D() {

	}

	void onAttach() override {
		HART_CLIENT_LOG(std::string("Attached layer: ") + getName());

		m_AspectRatio = Hart::Application::Get()->getWindowWidth() / (float)Hart::Application::Get()->getWindowHeight();
		m_Camera = std::make_shared<Hart::PerspectiveCamera>(fovD, m_AspectRatio);
		m_Camera->setPosition({ 0.0f, 0.0f, -3.0f });
		m_Camera->setFront({ 0.0f, 0.0f, -1.0f });
		m_Camera->setWorldUp({ 0.0f, 1.0f, 0.0f });

		Hart::InputManager::DisableMouse();
	}

	void onDetach() override {
		HART_CLIENT_LOG(std::string("Detached layer: ") + getName());
	}

	void onEvent(Hart::Event& e) override {
		//HART_CLIENT_LOG(e);
		Hart::EventDispatcher eventDispatcher(e);

		eventDispatcher.dispatch<Hart::MouseMovedEvent>(BIND_EVENT_FUNC(Layer3D::onMouseMoved));
		eventDispatcher.dispatch<Hart::MouseWheelScrolledEvent>(BIND_EVENT_FUNC(Layer3D::onMouseWheelScrolled));
	}


	bool onMouseMoved(Hart::MouseMovedEvent& e) {
		float xpos = e.getXPos();
		float ypos = e.getYPos();

		auto [yaw, pitch, roll] = m_Camera->getRotation();

		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = lastX - xpos;
		float yoffset = ypos - lastY;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.03f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;


		yaw += xoffset;
		pitch += yoffset;

		if (pitch >= 89.0f) {
			pitch = 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}

		m_Camera->setRotation({ yaw, pitch, roll });

		return false;
	}

	bool onMouseWheelScrolled(Hart::MouseWheelScrolledEvent& e) {
		fovD -= e.getYOffset();
		if (fovD < 10.0f) {
			fovD = 10.0f;
		}
		if (fovD > 90.0f) {
			fovD = 90.0f;
		}

		m_Camera->setProjection(fovD, m_AspectRatio);

		return false;
	}

	void update(const float deltaTime) override {
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(Hart::Application::Get()->getCurrentFPS()));
		angle++;

		const float cameraSpeed = 8.0f * deltaTime;
		Hart::Vec3 cameraPos = m_Camera->getPosition();
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::W)) {
			cameraPos -= cameraSpeed * m_Camera->getFront();
		}
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::S)) {
			cameraPos += cameraSpeed * m_Camera->getFront();
		}

		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::A)) {
			cameraPos -= Hart::Vec3::ScalarMultiply(Hart::Vec3::GetNormal(Hart::Vec3::CrossProduct(m_Camera->getFront(), m_Camera->getWorldUp())), cameraSpeed);
		}
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::D)) {
			cameraPos += Hart::Vec3::ScalarMultiply(Hart::Vec3::GetNormal(Hart::Vec3::CrossProduct(m_Camera->getFront(), m_Camera->getWorldUp())), cameraSpeed);
		}

		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::Q)) {
			cameraPos.y -= cameraSpeed;
		}
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::E)) {
			cameraPos.y += cameraSpeed;
		}

		m_Camera->setPosition(cameraPos);

		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::F)) {
			float lastX = 960.0f / 2.0;
			float lastY = 540.0 / 2.0;
			bool firstMouse = true;

			Hart::InputManager::DisableMouse();
		}

		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::G)) {
			float lastX = 960.0f / 2.0;
			float lastY = 540.0 / 2.0;
			bool firstMouse = true;

			Hart::InputManager::EnableMouse();
		}
	}

	void render() override {
		Hart::Renderer3D::BeginScene(*m_Camera.get());

		for (size_t i = 0; i < cubePositions.size(); i++) {
			angle = 20.0f * i;
			Hart::Mat4 model = Hart::Mat4::Translate(cubePositions[i]) * Hart::Mat4::Rotate(angle, { 0.0f, 0.0f, 1.0f });

			Hart::Renderer3D::Submit(m_Vao, m_Shader, model);
		}

		Hart::Renderer3D::EndScene();
	}
};