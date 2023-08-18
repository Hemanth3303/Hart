#pragma once

#include "Hart.hpp"

#include "Graphics/Renderer/RenderCommand.hpp"

class Layer3D : public Hart::Layer {
private:
	std::shared_ptr<Hart::Graphics::VertexArray> vao;
	std::shared_ptr<Hart::Graphics::Shader> shader;
	float angle = 0.0f;
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

		vao = std::make_shared<Hart::Graphics::VertexArray>();
		Hart::Graphics::BufferLayout layout = {
			{ Hart::Graphics::ShaderDataType::Float3, "aPosition" },
			{ Hart::Graphics::ShaderDataType::Float4, "aColor" },
		};
		std::shared_ptr <Hart::Graphics::VertexBuffer> vbo=std::make_shared<Hart::Graphics::VertexBuffer>(vertices, (uint32_t)sizeof(vertices));
		vbo->setLayout(layout);
		vao->addVertexBuffer(vbo);
		std::shared_ptr<Hart::Graphics::IndexBuffer> ibo = std::make_shared<Hart::Graphics::IndexBuffer>(indices, (uint32_t)(sizeof(indices) / sizeof(uint32_t)));
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

	void onEvent(Hart::Events::Event& e) override {
		//HART_CLIENT_LOG(e);
	}

	void update(const float deltaTime) override {
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(Hart::Application::Get()->getCurrentFPS()));
		angle++;
	}

	void render() override {
		shader->bind();
		auto aspectRatio = Hart::Application::Get()->getWindowWidth() / (float)Hart::Application::Get()->getWindowHeight();
		auto persp = Hart::Maths::Mat4::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
		auto view = Hart::Maths::Mat4::translate({ 0.0f, 0.0f, -3.0f });
		auto axis = Hart::Maths::Vec3::getNormal({ 1, 1, 1 });
		auto model = Hart::Maths::Mat4::rotate(angle, axis);
		shader->setUniform("uProjection", persp);
		shader->setUniform("uView", view);
		shader->setUniform("uModel", model);

		Hart::Graphics::RenderCommand::DrawIndexed(vao);
	}
};