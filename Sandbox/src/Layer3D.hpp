#pragma once

#include "Hart.hpp"

#include "Graphics/Renderer/RenderCommand.hpp"

class Layer3D : public Hart::Layer {
private:
	std::shared_ptr<Hart::VertexArray> vao;
	std::shared_ptr<Hart::Shader> shader;
	float angle = 0.0f;

	Hart::Vec3 cameraPos = { 0.0f, 0.0f, -3.0f };
	Hart::Vec3 cameraFront = { 0.0f, 0.0f, -1.0f };
	Hart::Vec3 cameraUp = { 0.0f, 1.0f, 0.0f };

	bool firstMouse = true;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 960.0f / 2.0;
	float lastY = 540.0 / 2.0;
	float fovD = 45.0f;
public:
	Layer3D(const std::string& name = "Layer3D")
		: Layer(name) {

		float vertices[7 * 8] = {
			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.75f, //0
			 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.75f, //1
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.75f, //2
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.75f, //3
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.75f, //4
			 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.75f, //5
			-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.75f, //6
			 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.75f, //7
		};
		uint32_t indices[] = {
			//Top
			2, 6, 7,
			2, 3, 7,

			//Bottom
			0, 4, 5,
			0, 1, 5,

			//Left
			0, 2, 6,
			0, 4, 6,

			//Right
			1, 3, 7,
			1, 5, 7,

			//Front
			0, 2, 3,
			0, 1, 3,

			//Back
			4, 6, 7,
			4, 5, 7
		};

		vao = std::make_shared<Hart::VertexArray>();
		Hart::BufferLayout layout = {
			{ Hart::ShaderDataType::Float3, "aPosition" },
			{ Hart::ShaderDataType::Float4, "aColor" },
		};
		std::shared_ptr <Hart::VertexBuffer> vbo=std::make_shared<Hart::VertexBuffer>(vertices, (uint32_t)sizeof(vertices));
		vbo->setLayout(layout);
		vao->addVertexBuffer(vbo);
		std::shared_ptr<Hart::IndexBuffer> ibo = std::make_shared<Hart::IndexBuffer>(indices, (uint32_t)(sizeof(indices) / sizeof(uint32_t)));
		ibo->bind();
		vao->setIndexBuffer(ibo);
		shader = Hart::Application::Get()->getShader("DefaultShader3D");
		shader->bind();

	}

	~Layer3D() {

	}

	void onAttach() override {
		HART_CLIENT_LOG(std::string("Attached layer: ") + getName());
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

		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f;
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

		Hart::Vec3 front;
		front.x = static_cast<float>(Hart::cosD(yaw) * Hart::cosD(pitch));
		front.y = static_cast<float>(Hart::sinD(pitch));
		front.z = static_cast<float>(Hart::sinD(yaw) * Hart::cosD(pitch));
		cameraFront = Hart::Vec3::GetNormal(front);

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

		return false;
	}

	void update(const float deltaTime) override {
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(Hart::Application::Get()->getCurrentFPS()));
		angle++;

		const float cameraSpeed = 8.0f * deltaTime;
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::W)) {
			cameraPos += cameraSpeed * cameraFront;
		}
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::S)) {
			cameraPos -= cameraSpeed * cameraFront;
		}

		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::A)) {
			cameraPos -= Hart::Vec3::ScalarMultiply(Hart::Vec3::GetNormal(Hart::Vec3::CrossProduct(cameraFront, cameraUp)), cameraSpeed);
		}
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::D)) {
			cameraPos += Hart::Vec3::ScalarMultiply(Hart::Vec3::GetNormal(Hart::Vec3::CrossProduct(cameraFront, cameraUp)), cameraSpeed);
		}

		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::Q)) {
			cameraPos.y += cameraSpeed;
		}
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::E)) {
			cameraPos.y -= cameraSpeed;
		}

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
		shader->bind();
		auto aspectRatio = Hart::Application::Get()->getWindowWidth() / (float)Hart::Application::Get()->getWindowHeight();
		auto persp = Hart::Mat4::Perspective(fovD, aspectRatio, 0.1f, 100.0f);

		Hart::Mat4 view = Hart::Mat4::LookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		auto axis = Hart::Vec3::GetNormal({ 1, 1, 1 });
		auto model = Hart::Mat4::Rotate(angle, axis);

		shader->setUniform("uProjection", persp);
		shader->setUniform("uView", view);
		shader->setUniform("uModel", model);

		Hart::RenderCommand::DrawIndexed(vao);
	}
};